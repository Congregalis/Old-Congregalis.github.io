#include <stdio.h>
#include <stdlib.h>

typedef struct{
     int id;
     int level;
     int cometime;
     int servertime;
     int waittime;
     int finishtime;
     int turnovertime;
}JOB;

JOB jobs[7]={
     1,0,800,50,0,0,0,
     2,1,815,30,0,0,0,
     3,2,830,25,0,0,0,
     4,2,835,20,0,0,0,
     5,2,845,15,0,0,0,
     6,1,700,10,0,0,0,
     7,0,820,5,0,0,0,
};

int compare1(const void *a, const void *b){
    return ((JOB*)a)->cometime - ((JOB*)b)->cometime;
}

void FCFS(){
    qsort(jobs,7,sizeof(JOB),compare1);
    int i = 0;
    int totalwait = 0, totalturnover = 0;
    float averagewait = 0, averageturnover = 0;
    for(;i<7;i++){
        if(i==0||(i>0 && jobs[i-1].finishtime <= jobs[i].cometime)){
              jobs[i].waittime = 0;
              jobs[i].turnovertime = jobs[i].servertime;
              jobs[i].finishtime = jobs[i].cometime + jobs[i].servertime;   
            }
        else{
              jobs[i].waittime = jobs[i-1].finishtime - jobs[i].cometime;
              jobs[i].turnovertime = jobs[i].waittime + jobs[i].servertime;
              jobs[i].finishtime = jobs[i-1].finishtime + jobs[i].servertime;
            }
        totalwait += jobs[i].waittime;
        totalturnover += jobs[i].turnovertime;
		//printf("第%d个进程: 等待时间为%d，周转时间为%d\n", i, jobs[i].waittime, jobs[i].turnovertime);
    }
    averagewait = totalwait / 7;
    averageturnover = totalturnover / 7;
    printf("FCFS:\n 总等待时间: %d\n 总周转时间: %d\n 平均等待时间: %.1f\n 平均周转时间: %.1f\n\n", totalwait, totalturnover, averagewait, averageturnover);
}

void SJF(){
    int vis[7] = {0};
    int stop = 0;
    qsort(jobs, 7, sizeof(JOB), compare1);
    int totalwait = 0, totalturnover = 0;
	float averagewait = 0, averageturnover = 0;
    int finish = 0;
    while(stop < 7){
         int i = 0;
         for(;i < 7; i++)
            if(jobs[i].cometime > finish)
               break;
         int j = i-1;
         int flag = 0;
         int idx = -1, shortest = 10000;
         for(;j >= 0;j--){
                if(vis[j])
                    continue;
                else{
                    flag = 1;
                    if(jobs[j].servertime < shortest){
                         shortest = jobs[j].servertime;
                         idx = j;
                     }
                  }
         }
         if(!flag){
             vis[i] = 1;
             jobs[i].waittime = 0;
             jobs[i].turnovertime = jobs[i].servertime;
             finish = jobs[i].cometime + jobs[i].servertime;
             jobs[i].finishtime  = finish;
             totalwait +=jobs[i].waittime;
             totalturnover += jobs[i].turnovertime;
         }
         else{
             vis[idx] = 1;
             jobs[idx].waittime = finish - jobs[idx].cometime;
             jobs[idx].turnovertime = jobs[idx].waittime + jobs[idx].servertime;
             finish += jobs[idx].servertime;
             jobs[idx].finishtime = finish;
             totalwait += jobs[idx].waittime;
             totalturnover += jobs[idx].turnovertime;
         }
         stop = vis[0]+vis[1]+vis[2]+vis[3]+vis[4]+vis[5]+vis[6];
    }
    averagewait = totalwait / 7;
    averageturnover = totalturnover / 7;
    printf("SJF: \n 总等待时间: %d\n 总周转时间: %d\n 平均等待时间: %.1f\n 平均周转时间: %.1f\n\n", totalwait, totalturnover, averagewait, averageturnover);
}

void Priority(){
    int vis[7] = {0};
    int stop = 0;
    qsort(jobs, 7, sizeof(JOB), compare1);
    int totalwait = 0, totalturnover = 0;
	float averagewait = 0 ,averageturnover = 0;
    int finish = 0;
    while(stop < 7){
         int i = 0;
         for(;i<7;i++)
               if(jobs[i].cometime > finish)
                  break;
         int j = i-1;
         int flag = 0;
         int idx = -1, pri = -1;
         for(;j >= 0; j--){
             if(vis[j])
                  continue;
             else{
                  flag = 1;
                  if(jobs[j].level > pri){
                      pri = jobs[j].level;
                      idx = j;
                   }
                  else if(jobs[j].level == pri){
                      idx = jobs[j].cometime < jobs[idx].cometime ? j : idx;
                   }
                }
         }
         if(!flag){
             vis[i] = 1;
             jobs[i].waittime = 0;
             jobs[i].turnovertime = jobs[i].servertime;
             finish = jobs[i].cometime + jobs[i].servertime;
             jobs[i].finishtime = finish;
             totalwait += jobs[i].waittime;
             totalturnover += jobs[i].turnovertime;
         }
         else{
             vis[idx] = 1;
             jobs[idx].waittime = finish - jobs[idx].cometime;
             jobs[idx].turnovertime = jobs[idx].waittime +jobs[idx].servertime;
             finish += jobs[idx].servertime;
             jobs[idx].finishtime = finish;
             totalwait += jobs[idx].waittime;
             totalturnover += jobs[idx].turnovertime;
         }
         stop = vis[0]+vis[1]+vis[2]+vis[3]+vis[4]+vis[5]+vis[6];
    }
    averagewait = totalwait / 7;
    averageturnover = totalturnover / 7;
    printf("Priority: \n 总等待时间: %d\n 总周转时间: %d\n 平均等待时间: %.1f\n 平均周转时间: %.1f\n\n", totalwait, totalturnover, averagewait, averageturnover);
}

int main()
{
   FCFS();
   SJF();
   Priority();
   return 0;
}
