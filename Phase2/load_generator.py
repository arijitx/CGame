import threading
import time
import sys
import requests
import pandas as pd
import matplotlib.pyplot as plt
import subprocess
import os
import signal


all_started=threading.Event()

class user_obj (threading.Thread):
    def __init__(self, tid):
      threading.Thread.__init__(self)
      self.tid=tid
      self.resp_time=0
      self.req_count=0
      self.success_count=0

    def run(self):
      all_started.wait()
      while(testing):
          t_prev=time.time()
          flag,t=req()
          if flag:
            self.resp_time+=t-t_prev
            self.req_count+=1
            self.success_count+=1
          else:
            self.resp_time=t-t_prev
            self.req_count+=1
          time.sleep(.1)



def req():
    try:
        r = requests.get('http://localhost:8080/',timeout=10.0)
        return True,time.time()
    except:
        return False,time.time()


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
    testing=False
    for i in range(N):
        threads[i]=user_obj(i)
    print('Thread Created')
    print('--'*30)

    for i in range(N):
        threads[i].start()

    all_started.set()
    testing=True
    print('Starting Test for N :',N)
    time.sleep(test_time)
    print('Test Completed')
    testing=False
    total_time=0
    total_req_count=0
    total_success_count=0
    for i in range(N):
        threads[i].join()
        total_time+=threads[i].resp_time
        total_req_count+=threads[i].req_count
        total_success_count+=threads[i].success_count

    td={}
    td['N']=N
    td['total_time']=total_time
    td['total_req_count']=total_req_count
    td['avg_resp_time']=total_time/total_req_count
    td['success_count']=total_success_count
    td['tp']=total_success_count/test_time
    print('Test Details')
    for x in td:
        print(x,td[x])
    print('--'*30)
    print()
    all_started.clear()
    return td

for N in range(N_min,N_max+1,step):
    pro = subprocess.Popen('./server.out', stdout=subprocess.PIPE,shell=True, preexec_fn=os.setsid)
    print('Started Server Pid :',os.getpgid(pro.pid))
    td=test(N)
    test_data.append(td)
    os.killpg(os.getpgid(pro.pid), signal.SIGTERM)
    time.sleep(2)

fig,ax=plt.subplots()
df_td=pd.DataFrame(test_data)
# df_td=pd.read_csv('results.csv')
df_td['throughtput']=df_td['tp']
df_td.to_csv("results.csv",index=False)
ax.plot(df_td['N'],df_td['avg_resp_time'])
ax.scatter(df_td['N'],df_td['avg_resp_time'],color='red')
#ax.scatter(df_td['N'],df_td['avg_resp_time'],color='red')
ax.set_ylabel('Turn around Time')
ax.set_title('TAT vs Number of users')
ax.set_xlabel('Nmmber of users')
fig.savefig('tat.png')
plt.close(fig);
print("here ")
fig,ax=plt.subplots()
ax.plot(df_td['N'],df_td['throughtput'])
ax.scatter(df_td['N'],df_td['throughtput'],color='red')
ax.set_ylabel('Throughput')
ax.set_title('Throughput vs Number of users')
ax.set_xlabel('Number of users')
fig.savefig('throughput.png')

plt.close(fig)
#print the throughtput
