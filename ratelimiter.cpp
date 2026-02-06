#include <iostream>
#include <queue>

using namespace std;

class RateLimiter {
private: 
    int N;
    queue<int> requestTimestamps;
public:
    RateLimiter(int N) : N(N) {}

    bool isRequestAllowed(int timestamp){
        while(requestTimestamps.empty() == false && requestTimestamps.front() <= timestamp - 60){
            requestTimestamps.pop();
        }

        return requestTimestamps.size() < N;
    }

    void addRequest(int timestamp){
        requestTimestamps.push(timestamp);
    }
};

class TrafficManager {
private:
    RateLimiter* rateLimiter;

public:
    TrafficManager(RateLimiter* rateLimiter) : rateLimiter(rateLimiter) {}

    bool request(int timestamp) {
        if(rateLimiter->isRequestAllowed(timestamp)){
            rateLimiter->addRequest(timestamp);
            return true; 
        }
        return false;
    }
};

int main() {
    RateLimiter* ratelimiter = new RateLimiter(5);
    TrafficManager* trafficManager = new TrafficManager(ratelimiter);

    // for(int i=1;i<=6;i++){
    //     if(trafficManager->request(i)){
    //         cout << "Request at timestamp " << i << " is allowed." << endl;
    //     } else {
    //         cout << "Request at timestamp " << i << " is denied." << endl;
    //     }
    // }

    cout << trafficManager->request(1) << endl;  // true
    cout << trafficManager->request(10) << endl; // true            
    cout << trafficManager->request(20) << endl; // true
    cout << trafficManager->request(30) << endl; // true
    cout << trafficManager->request(40) << endl; // true
    cout << trafficManager->request(50) << endl; // false
    cout << trafficManager->request(61) << endl; // true

    delete trafficManager;
    delete ratelimiter;

    return 0;
}