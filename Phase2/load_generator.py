import requests
from time import time
import threading
import _thread

requests_count=0
time_count=0

lamda=200
time_between_reqs=1/lamda
test_start_time=time()

lock = threading.Lock()
response_count=0
response_time=0
def req(t):
    try:
        r = requests.get('http://10.15.28.175:8080')
        global response_time
        global response_count
        if(r.status_code==200):
            lock.acquire()
            response_time=(response_time*response_count+time()-t)/(response_count+1)
            response_count+=1
            lock.release()

    except:
        return


diff=0
start_time=time()
prev_req_count=1
while(True):
    if(requests_count/100>prev_req_count):
        print('Request Count : ',requests_count,' Time Elapsed : ',time()-test_start_time,' Lamda : ',requests_count/(time()-test_start_time),\
        ' Response Count : ',response_count,' Avg Response Time : ',response_time)
        prev_req_count=int(requests_count/100)+1
    time_diff=(time()-start_time)/time_between_reqs
    if(int(time_diff)>1.):

        diff+=(time_diff-int(time_diff))
        for i in range(int(time_diff)):
            requests_count+=1
            _thread.start_new_thread(req,(time(),))
        start_time=time()
    if(diff>1.0):
        requests_count+=1
        _thread.start_new_thread(req,(time(),))
        diff=diff-1
