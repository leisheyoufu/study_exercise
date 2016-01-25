#!/usr/bin/env python
#coding=utf8

import requests
import os
import exceptions

class PcenterClient(object):

    def __init__(self, api_url, verify=None, cert=None):
        self.api_url = api_url.rstrip('/')
        self.verify = verify
        self.cert = cert
        adapter = requests.adapters.HTTPAdapter(pool_connections=100,
                                                pool_maxsize=1000)
        self.session = requests.Session()
        self.session.mount(self.api_url, adapter)

    def _request(self, method, path, data=None):
        request_url = '{api_url}{path}'.format(api_url=self.api_url, path=path)
        request_headers = {
            'Content-Type': 'application/json',
            'Accept': 'application/json',
        }

        return self.session.request(method,
                                    request_url,
                                    headers=request_headers,
                                    data=data,
                                    verify=self.verify,
                                    cert=self.cert)

    def get(self, path, **kwargs):
        return self._request('GET', path, data=kwargs)

    def head(self, path, kwargs):
        return self._request('HEAD', path, data=kwargs)

    def post(self, path, kwargs):
        return self._request('POST', path, data=kwargs)

    def put(self, path, kwargs):
        return self._request('PUT', path, data=kwargs)

    def delete(self, path, kwargs):
        return self._request('DELETE', path, data=kwargs)

    def patch(self, path, kwargs):
        return self._request('PATCH', path, data=kwargs)

if __name__ == "__main__":
    client = PcenterClient("https://x3650m4n03/", "/root/cert/ca.pem")
    response = client.get("/pcenterws/nodes?userName=wsuser&password=pcenter")
    print response

"""

  status_code = response.status_code
        if status_code != 200:
            msg = response.reason
            #TODO(chenglch) add log error here
            raise exceptions
        result = response.json()
        import pdb
        pdb.set_trace()
        print response
"""