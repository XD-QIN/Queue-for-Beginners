clear
T = 1e6;
N = 1000;
lambda = [0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9];
mu = 1.0;
QueueLength = zeros(N, length(lambda));
totalQ = zeros(N, length(lambda));
avgQ = zeros(1, length(lambda));
theoryQ = zeros(1, length(lambda));

for i = 1 : length(lambda)
    for t = 1 : (T-1)
        u = rand();
        M = 0; %total number of active servers
        ActiveServerID = zeros(1, N);
        for n = 1 : N %sample the active numbe of servers and servers' ID
            if QueueLength(n,i) > 0
                ActiveServerID(1, M+1) = n;
                M = M + 1;
            end
        end    
        if u < N * lambda(1, i)/ (N * lambda(1, i) + M * mu)%arrival event happens
           randSampleArrival = randi([1 N],1,2);
           if QueueLength(randSampleArrival(1,1),i) > QueueLength(randSampleArrival(1,2),i)
               ArrivalNumber = randSampleArrival(1,2);
           elseif QueueLength(randSampleArrival(1,1),i) < QueueLength(randSampleArrival(1,2),i)
               ArrivalNumber = randSampleArrival(1,1);
           else
               randomChoose2 = randi([1 2],1,1);
               ArrivalNumber = randSampleArrival(1, randomChoose2);
           end
           for n = 1 : N
               if n == ArrivalNumber
                   QueueLength(n ,i) = QueueLength(n ,i) + 1;
               else
                   QueueLength(n ,i) =  QueueLength(n ,i);
               end
           end
        else    %depature event happens
            randSampleDepature =  randi([1 M],1,1);
            DepatureNum = ActiveServerID(1, randSampleDepature);
            for n = 1 : N
                if n == DepatureNum
                    QueueLength(n ,i) = max(QueueLength(n ,i)-1,0); 
                else
                    QueueLength(n ,i) =  QueueLength(n ,i);
                end
            end
        end
        totalQ(:,i) = totalQ(:,i) + QueueLength(:,i);         
    end
    avgQ(1,i) = mean(totalQ(:,i))/T;
    for j = 1 : 1e7
        theoryQ(1,i) = lambda(1,i)^(2^j-1) + theoryQ(1, i);
    end   
end

figure(1)
plot(lambda,theoryQ, 'r-s','LineWidth',2.5,'MarkerSize',6)
hold on
plot(lambda,avgQ, 'b-o','LineWidth',2.5,'MarkerSize',6)
legend('theoryQ','avgQ')
xlabel('lambda','FontSize',18)
ylabel('Average queue length','FontSize',18)
grid on