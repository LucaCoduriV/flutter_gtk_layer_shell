//
// Created by luca on 5/9/23.
//

#include "flutter_layer_shell.h"
#include <gtk-layer-shell/gtk-layer-shell.h>

#include <iostream>

#include "include/gtk_layer_shell/desktop_multi_window_plugin.h"
#include "desktop_multi_window_plugin_internal.h"

namespace {

    WindowCreatedCallback _g_window_created_callback = nullptr;

}

FlutterLayerShell::FlutterLayerShell(
        int64_t id,
        const std::string &args,
        const std::shared_ptr<FlutterWindowCallback> &callback
) : callback_(callback), id_(id) {
    window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_layer_init_for_window(GTK_WINDOW(window_));
    gtk_window_set_default_size(GTK_WINDOW(window_), 1280, 720);
    gtk_window_set_title(GTK_WINDOW(window_), "");
    gtk_window_set_position(GTK_WINDOW(window_), GTK_WIN_POS_CENTER);
    gtk_widget_show(GTK_WIDGET(window_));

    g_signal_connect(window_, "destroy", G_CALLBACK(+[](GtkWidget *, gpointer arg) {
        auto *self = static_cast<FlutterLayerShell *>(arg);
        if (auto callback = self->callback_.lock()) {
            callback->OnWindowClose(self->id_);
            callback->OnWindowDestroy(self->id_);
        }
    }), this);

    g_autoptr(FlDartProject)
    project = fl_dart_project_new();
    const char *entrypoint_args[] = {"multi_window", g_strdup_printf("%ld", id_), args.c_str(), nullptr};
    fl_dart_project_set_dart_entrypoint_arguments(project, const_cast<char **>(entrypoint_args));

    auto fl_view = fl_view_new(project);
    gtk_widget_show(GTK_WIDGET(fl_view));
    gtk_container_add(GTK_CONTAINER(window_), GTK_WIDGET(fl_view));

    if (_g_window_created_callback) {
        _g_window_created_callback(FL_PLUGIN_REGISTRY(fl_view));
    }
    g_autoptr(FlPluginRegistrar)
    desktop_multi_window_registrar =
            fl_plugin_registry_get_registrar_for_plugin(FL_PLUGIN_REGISTRY(fl_view), "DesktopMultiWindowPlugin");
    desktop_multi_window_plugin_register_with_registrar_internal(desktop_multi_window_registrar);

    window_channel_ = WindowChannel::RegisterWithRegistrar(desktop_multi_window_registrar, id_);

    gtk_widget_grab_focus(GTK_WIDGET(fl_view));
    gtk_widget_set_size_request (GTK_WIDGET(fl_view), 100, 100);
    gtk_widget_hide(GTK_WIDGET(window_));
}

WindowChannel *FlutterLayerShell::GetWindowChannel() {
    return window_channel_.get();
}

FlutterLayerShell::~FlutterLayerShell() = default;

void desktop_multi_window_plugin_set_layer_shell_created_callback(WindowCreatedCallback callback) {
    _g_window_created_callback = callback;
}
