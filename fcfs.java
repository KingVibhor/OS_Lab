package os;

import java.util.Scanner;

public class fcfs{
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        
        System.out.print("Enter the number of processes: ");
        int n = s.nextInt();
        
        int[] pid = new int[n]; 
        int[] at = new int[n];  
        int[] bt = new int[n];  
        int[] ct = new int[n];  
        int[] wt = new int[n];  
        int[] tat = new int[n]; 
        
        System.out.println("Enter the arrival times of the processes:");
        for (int i = 0; i < n; i++) {
            System.out.print("P" + (i + 1) + " arrival time: ");
            at[i] = s.nextInt();
            pid[i] = i + 1;
        }
        
        System.out.println("Enter the burst times of the processes:");
        for (int i = 0; i < n; i++) {
            System.out.print("P" + (i + 1) + " burst time: ");
            bt[i] = s.nextInt();
        }
        
        
        int currentTime = 0;
        for (int i = 0; i < n; i++) {
            if (currentTime < at[i]) {
                currentTime = at[i];
            }
            ct[i] = currentTime + bt[i];
            currentTime = ct[i];
        }
        
       
        for (int i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
        }
        
       
        float totalWT = 0, totalTAT = 0;
        for (int i = 0; i < n; i++) {
            totalWT += wt[i];
            totalTAT += tat[i];
        }
        float avgWT = totalWT / n;
        float avgTAT = totalTAT / n;
        
       
        System.out.println("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < n; i++) {
            System.out.println("P" + pid[i] + "\t\t" + at[i] + "\t\t" + bt[i] + "\t\t" + ct[i] + "\t\t" + tat[i] + "\t\t" + wt[i]);
        }
        System.out.println("\nAverage Waiting Time = " + avgWT);
        System.out.println("Average Turnaround Time = " + avgTAT);
        
        s.close();
    }
}