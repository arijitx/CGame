import threading
import time
import sys
import requests
import pandas as pd
import matplotlib.pyplot as plt

class user_obj (threading.Thread):
    def __init__(self, tid):
      threading.Thread.__init__(self)
      self.tid=tid
      self.resp_time=0
      self.req_count=0

    def run(self):
      while(testing):
          t_prev=time.time()
          t=req()
          if t=='fail':
              break
          self.resp_time=(self.resp_time*self.req_count+(t-t_prev))/(self.req_count+1)
          self.req_count+=1

def req():
    try:
        r = requests.get('http://10.15.28.175:8080/',timeout=1.0)
        return time.time()
    except:
        return 'fail'


testing =True

N_min=int(sys.argv[1])
N_max=int(sys.argv[2])
step=int(sys.argv[3])
test_time=int(sys.argv[4])

print('Closed Loop Load Gen')
print('====================')
print('Config\n-------')
print('N_min',N_min)
print('N_max',N_max)
print('Step',step)
print('Test Time',test_time,'Secs')
test_data=[]

def test(N):
    threads=[None]*N
    global testing
    testing=True
    for i in range(N):
        threads[i]=user_obj(i)

    for i in range(N):
        threads[i].start()
    print('Starting Test for N :',N)
    time.sleep(test_time)
    print('Test Completed')
    testing=False
    total_time=0
    total_req_count=0
    for i in range(N):
        threads[i].join()
        total_time+=threads[i].resp_time*threads[i].req_count
        total_req_count+=threads[i].req_count
    td={}
    td['N']=N
    td['total_time']=total_time
    td['total_req_count']=total_req_count
    td['avg_resp_time']=total_time/total_req_count

    return td

for N in range(N_min,N_max+1,step):
    td=test(N)
    test_data.append(td)

df_td=pd.DataFrame(test_data)
df_td.to_csv("results.csv",index=False)
plt.plot(df_td['N'],df_td['avg_resp_time'])
plt.scatter(df_td['N'],df_td['avg_resp_time'],color='red')
plt.savefig('plot.png')
plt.show()
