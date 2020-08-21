public class App : Gtk.Application {
    public App() {
        Object(
            application_id: "nl.plaatsoft.warquest",
            flags: ApplicationFlags.FLAGS_NONE
        );
    }

    protected override void activate() {
        var window = new Gtk.ApplicationWindow(this);
        window.icon_name = "applications-internet";
        window.default_width = 550;
        window.default_height = 800;
        window.resizable = false;

        var headerbar = new Gtk.HeaderBar();
        headerbar.title = "WarQuest";
        headerbar.show_close_button = true;
        window.set_titlebar(headerbar);

        var scrolled_window = new Gtk.ScrolledWindow(null, null);
        scrolled_window.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
        window.add(scrolled_window);

        var webview = new WebKit.WebView();
        var firstLoad = true;
        webview.load_changed.connect(() => {
            if (webview.title != null) {
                headerbar.title = webview.title;

                if (firstLoad) {
                    firstLoad = false;
                    webview.show();
                }
            }
        });
        scrolled_window.add(webview);

        window.show_all();
        webview.hide();

        webview.load_uri("https://warquest.plaatsoft.nl/");
    }

    public static int main(string[] args) {
        var app = new App();
        return app.run(args);
    }
}
