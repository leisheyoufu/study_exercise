__author__ = 'chenglong'
from six.moves import socketserver
from wsgiref import simple_server
from test_pecan_controller import app

class ThreadedSimpleServer(socketserver.ThreadingMixIn,
                           simple_server.WSGIServer):
    """A Mixin class to make the API service greenthread-able."""
    pass


def main():

    host = "0.0.0.0"
    port = 8081
    wsgi = simple_server.make_server(
            host, port,
            app.VersionSelectorApplication(),
            server_class=ThreadedSimpleServer)

    try:
        wsgi.serve_forever()
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()