load 'data_May10.mat'
figure(1)
plot(lambda,improvementRatio0_5,'r-s','LineWidth',2.5,'MarkerSize',10)
hold on
plot(lambda,improvementRatio1,'m-x','LineWidth',2.5,'MarkerSize',10)
plot(lambda,improvementRatio5,'g-o','LineWidth',2.5,'MarkerSize',10)
%plot(lambda,JOSavgX_M2, 'b-*','LineWidth',2.5,'MarkerSize',5)
plot(lambda,improvementRatio10, 'b-+','LineWidth',2.5,'MarkerSize',10)
plot(lambda,improvementRatio20, 'k-o','LineWidth',2.5,'MarkerSize',10)
legend({'C=0.5', 'C=1','C=5', 'C=10', 'C=20'}, 'FontSize', 14)
xlabel('\lambda','FontSize',18)
ylabel('improvement ratio (%)', 'FontSize', 18)
grid on