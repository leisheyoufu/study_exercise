# Reference https://www.cnblogs.com/aloe-n/p/10412391.html

import asyncio
import aiohttp
import json


async def get_json(client, url):
    async with client.get(url) as response:
        assert response.status == 200
        return await response.read()


async def get_36_kr(page, client):
    data1 = await get_json(client, 'https://36kr.com/api/search-column/mainsite?per_page=20&page={}'.format(page))
    # j = json.loads(data1.decode('utf-8'))

    # with open(f"./{page}.json", "w", encoding='utf-8') as f:
    #     f.write(json.dumps(j, indent=2, ensure_ascii=False))

    print('Http1 with page:', page)

async def get_36_kr2(page, client):
    url = f'https://36kr.com/api/search-column/mainsite?per_page=1&page={page}'
    async with client.get(url, ssl=False) as response:
        assert response.status == 200
        print('Http2 with page:', page)
        return page


async def main2():
    async with aiohttp.ClientSession() as client:
        tasks = [asyncio.ensure_future(get_36_kr2(i, client))
                 for i in range(20)]
        res = await asyncio.gather(*tasks)
        print(json.dumps(res,indent=2))

async def main():
    print(type(loop))
    client = aiohttp.ClientSession(loop=loop) # CL: loop only available in async main function, interesting
    tasks = [asyncio.ensure_future(get_36_kr(i, client)) for i in range(20)]
    await asyncio.gather(*tasks)
    await client.close()

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
    loop.run_until_complete(main2())
    loop.close()