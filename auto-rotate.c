#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define RR_Rotate_0    0
#define RR_Rotate_90   1
#define RR_Rotate_180  2
#define RR_Rotate_270  3

static GMainLoop *loop;
static GDBusProxy *iio_proxy;

static void rotate_screen(int new_rotation) {
	const char *rotation_command;

	switch (new_rotation) {
		case RR_Rotate_0:
			rotation_command = "output.1.rotation.normal"; // Normal orientation
			break;
		case RR_Rotate_90:
			rotation_command = "output.1.rotation.left";   // 90 degrees left
			break;
		case RR_Rotate_180:
			rotation_command = "output.1.rotation.inverted";  // 180 degrees
			break;
		case RR_Rotate_270:
			rotation_command = "output.1.rotation.right";   // 270 degrees right
			break;
		default:
			g_print("Invalid rotation value\n");
			return;
	}

	// Create the command to execute
	char command[256];
	snprintf(command, sizeof(command), "kscreen-doctor %s", rotation_command);

	// Execute the command
	int ret = system(command);
	if (ret == -1) {
		g_print("Error executing kscreen-doctor\n");
	} else {
		g_print("Screen rotated to %s\n", rotation_command);
	}
}

static void properties_changed(GDBusProxy *proxy, GVariant *changed_properties,
							   GStrv invalidated_properties, gpointer user_data) {
	GVariant *v;
	GVariantDict dict;

	g_variant_dict_init(&dict, changed_properties);

	if (g_variant_dict_contains(&dict, "AccelerometerOrientation")) {
		v = g_dbus_proxy_get_cached_property(iio_proxy, "AccelerometerOrientation");

		int new_rotation;
		char recognized = 1;

		if (g_strcmp0(g_variant_get_string(v, NULL), "normal") == 0) {
			new_rotation = RR_Rotate_0;
		} else if (g_strcmp0(g_variant_get_string(v, NULL), "left-up") == 0) {
			new_rotation = RR_Rotate_90;
		} else if (g_strcmp0(g_variant_get_string(v, NULL), "bottom-up") == 0) {
			new_rotation = RR_Rotate_180;
		} else if (g_strcmp0(g_variant_get_string(v, NULL), "right-up") == 0) {
			new_rotation = RR_Rotate_270;
		} else {
			recognized = 0;
		}

		if (recognized) {
			rotate_screen(new_rotation);
		}

		g_variant_unref(v);
	}
							   }

							   static void appeared_cb(GDBusConnection *connection, const gchar *name,
													   const gchar *name_owner, gpointer user_data) {
								   GError *error = NULL;

								   g_print("+++ iio-sensor-proxy appeared\n");

								   iio_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
																			 G_DBUS_PROXY_FLAGS_NONE,
													 NULL,
													 "net.hadess.SensorProxy",
													 "/net/hadess/SensorProxy",
													 "net.hadess.SensorProxy",
													 NULL, NULL);

								   g_signal_connect(G_OBJECT(iio_proxy), "g-properties-changed",
													G_CALLBACK(properties_changed), NULL);

								   g_dbus_proxy_call_sync(iio_proxy, "ClaimAccelerometer",
														  NULL, G_DBUS_CALL_FLAGS_NONE,
								  -1, NULL, &error);
								   g_assert_no_error(error);
													   }

													   static void vanished_cb(GDBusConnection *connection, const gchar *name,
																			   gpointer user_data) {
														   if (iio_proxy) {
															   g_clear_object(&iio_proxy);
															   g_print("--- iio-sensor-proxy vanished, waiting for it to appear\n");
														   }
																			   }

																			   int main(int argc, char **argv) {
																				   loop = g_main_loop_new(NULL, TRUE);

																				   g_bus_watch_name(G_BUS_TYPE_SYSTEM, "net.hadess.SensorProxy",
																									G_BUS_NAME_WATCHER_FLAGS_NONE, appeared_cb,
										vanished_cb, NULL, NULL);

																				   g_print("Waiting for iio-sensor-proxy to appear...\n");
																				   g_main_loop_run(loop);

																				   return 0;
																			   }
