#include <libwebsockets.h>



static const struct lws_http_mount _default_dynamic_mount = {
	/* .mount_next */NULL,/* linked-list "next" */
	/* .mountpoint */"/dyn",/* mountpoint URL */
	/* .origin */NULL, /* serve from dir */
	/* .def */NULL,/* default filename */
	/* .protocol */"http",
	/* .cgienv */NULL,
	/* .extra_mimetypes */NULL,
	/* .interpret */NULL,
	/* .cgi_timeout */0,
	/* .cache_max_age */0,
	/* .auth_mask */0,
	/* .cache_reusable */0,
	/* .cache_revalidate */0,
	/* .cache_intermediaries */0,
	/* .origin_protocol */LWSMPRO_CALLBACK,/* files in a dir */
	/* .mountpoint_len */4,/* char count */
	/* .basic_auth_login_file */NULL,
};

static const struct lws_http_mount _default_mount = {
	/* .mount_next */&_default_dynamic_mount,/* linked-list "next" */
	/* .mountpoint */"/",/* mountpoint URL */
	/* .origin */"./www", /* serve from dir */
	/* .def */"index.html",/* default filename */
	/* .protocol */NULL,
	/* .cgienv */NULL,
	/* .extra_mimetypes */NULL,
	/* .interpret */NULL,
	/* .cgi_timeout */0,
	/* .cache_max_age */0,
	/* .auth_mask */0,
	/* .cache_reusable */0,
	/* .cache_revalidate */0,
	/* .cache_intermediaries */0,
	/* .origin_protocol */LWSMPRO_FILE,/* files in a dir */
	/* .mountpoint_len */1,/* char count */
	/* .basic_auth_login_file */NULL,
};

static int _callback_dynamic_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);



