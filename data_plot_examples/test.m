rho = 0.5;
B = 0 : 1 :10;
E_Q = rho / (1 - rho) - (B+1).* rho.^(B+1)./(1 - rho.^(B+1));

plot(B, E_Q, 'r-s','LineWidth',2.5,'MarkerSize',10)
%hold on
%plot(B, E_Q_paper, 'b-+','LineWidth',2.5,'MarkerSize',10)
xlabel('B','FontSize',18)
ylabel('E_Q','FontSize',18)
legend({'EQ'}, 'FontSize', 18)
title('\rho='+string(rho), 'FontSize', 15)
grid on
