load 'data_Jan23.mat'
figure(1)
plot(lambda,LocalFirstAvgX,'r-s','LineWidth',2.5,'MarkerSize',5)
hold on
plot(lambda,EdgeFirstAvgX,'m-x','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgX_M1,'g-o','LineWidth',2.5,'MarkerSize',5)
%plot(lambda,JOSavgX_M2, 'b-*','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgX_M5, 'b-+','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgX_M10, 'k-o','LineWidth',2.5,'MarkerSize',5)
legend('LFOS', 'EFOS','LC-JOS(M=1)', 'LC-JOS(M=5)', 'LC-JOS(M=10)')
xlabel('mean arrival rate','FontSize',18)
ylabel('average virtual queue length','FontSize',18)
grid on

figure(2)
plot(lambda,LocalFirstAvgP,'r-s','LineWidth',2.5,'MarkerSize',5)
hold on
plot(lambda,EdgeFirstAvgP,'m-x','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgP_M1,'g-o','LineWidth',2.5,'MarkerSize',5)
%plot(lambda,JOSavgP_M2, 'b-*','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgP_M5, 'b-+','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSavgP_M10, 'k-*','LineWidth',2.5,'MarkerSize',5)
legend('LocalFirst', 'EdgeFirst','LC-JOS(M=1)' ,'LC-OS(M=5)', 'LC-JOS(M=10)')
xlabel('Mean Arrival Rate','FontSize',18)
ylabel('Average Energy Consumption','FontSize',18)
grid on

figure(3)
plot(avgX_1_5, avgP_1_5, 'b-o','LineWidth',2.5,'MarkerSize',5)
hold on
%plot(avgX_2_5,avgP_2_5, 'b-*','LineWidth',2.5,'MarkerSize',5)
%plot(avgX_3_5,avgP_3_5, 'm-+','LineWidth',2.5,'MarkerSize',5)
%legend('lambda=1.5')
xlabel('average virtual queue length','FontSize',18)
ylabel('average energy consumption','FontSize',18)
grid on

figure(4)
plot(lambda,edgeP_ratio*100,'r-s','LineWidth',2.5,'MarkerSize',5)
hold on
plot(lambda,JOSP_ratio_M1*100, 'm-+','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSP_ratio_M5*100, 'g-*','LineWidth',2.5,'MarkerSize',5)
plot(lambda,JOSP_ratio_M10*100, 'b-o','LineWidth',2.5,'MarkerSize',5)
legend( 'EFOS','LC-JOS(M=1)' ,'LC-JOS(M=5)','LC-JOS(M=10)')
xlabel('mean arrival rate','FontSize',18)
ylabel('energy saving percentage (%)','FontSize',18)
grid on