%%% M/M/1/B %%%
%%% uniformization approach %%%

clear
T = 1e6; % simulation time
lambda = 0 : 0.1 : 1.8; %arrival rate
% lambda = 0 : 0.1 : 1.9; there is a bug under this setup
mu = 1; % local service rate
rho = lambda./ mu;
QueueLength = zeros(1, length(lambda));
TotalArrivalCount = zeros(1, length(lambda));
GlobalCount = zeros(1, length(lambda));
pi_B = zeros(1, length(lambda));
TheoryPi_B = zeros(1, length(lambda));
NumberOfJobInGlobal = zeros(1, length(lambda));
totalQ = zeros(1, length(lambda));
avgQ = zeros(1, length(lambda));
TheoryAvgQ = zeros(1, length(lambda));
B = zeros(1, length(lambda)) + 10;

for i =  1 : length(lambda)
    for t = 1 : T
         u = rand();
         if u <  lambda(1, i)/( lambda(1, i) +   mu) % arrival process
             TotalArrivalCount(1, i) = TotalArrivalCount(1, i) + 1;
             if QueueLength(1, i) < B(1, i)
                 QueueLength(1, i) = QueueLength(1, i) + 1;
             else
                 NumberOfJobInGlobal(1, i) = NumberOfJobInGlobal(1, i) + 1;
                 GlobalCount(1, i) = GlobalCount(1, i) + 1;
             end
         else 
             QueueLength(1, i) = max(QueueLength(1, i) - 1, 0);
         end
         totalQ(:,i) = totalQ(:,i) + QueueLength(:,i);
    end
    avgQ(1,i) = mean(totalQ(:,i))/T;
    pi_B(1, i) = GlobalCount(1, i) / TotalArrivalCount(1, i);
    if lambda(1,i) ~= mu
        TheoryAvgQ(1, i) = (B(1, i) + 1)/(rho(1,i)^(B(1,i)+1) - 1) + B(1, i) + 1/(1 - rho(1,i));
        TheoryPi_B(1, i) = (rho(1, i)^B(1,i) - rho(1, i)^(B(1,i)+1))/(1 - rho(1, i)^(B(1,i)+1));
    else
        TheoryAvgQ(1, i) = B(1, i) / 2;
        TheoryPi_B(1, i) = 1 / (B(1, i) + 1);
    end
end

figure(3)
plot(lambda,TheoryAvgQ, 'r-s','LineWidth',2.5,'MarkerSize',6)
hold on
plot(lambda,avgQ, 'b-o','LineWidth',2.5,'MarkerSize',6)
legend({'theoryQ','avgQ'},'FontSize', 15)
xlabel('lambda','FontSize',15)
ylabel('Average queue length','FontSize',15)
grid on

figure(4)
plot(lambda,TheoryPi_B, 'r-s','LineWidth',2.5,'MarkerSize',6)
hold on
plot(lambda,pi_B, 'b-o','LineWidth',2.5,'MarkerSize',6)
legend({'theoryQ','avgQ'},'FontSize', 15)
xlabel('lambda','FontSize',15)
ylabel('Average queue length','FontSize',15)
grid on