Example code for `elasticsearch-py`
===================================

reference: https://github.com/elastic/elasticsearch-py
This example code demonstrates the features and use patterns for the Python client.

To run this example make sure you have elasticsearch running on port 9200,
install additional dependencies (on top of `elasticsearch-py`)::

    pip install python-dateutil GitPython

And now you can load the index (the index will be called `git`)::

    python load.py

This will create an index with mappings and parse the git information of this
repository and load all the commits into it. You can run some sample queries by
running::

    python queries.py

Look at the `queries.py` file for querying example and `load.py` on examples on
loading data into elasticsearch. Both `load` and `queries` set up logging so in
`/tmp/es_trace.log` you will have a transcript of the commands being run in the
curl format.

Some useful example ::

  curl -XDELETE -k 'http://127.0.0.1:9200/git'  # delete git index
  curl -XGET 'localhost:9200'  # check elasticsearch versoin
