class Solution {
    public:
        long long countPairs(vector<int>& nums, int k) {
    
            vector<int>cnt(100100);
            for(auto num:nums){
                cnt[num]++;
            }
            vector<int>cnt2(100100);
    
    
            for(int i=1;i<100100;i++){
                for(int j=i;j<100100;j+=i){
                    cnt2[i]+=cnt[j];
                }
            }
            long long ans=0;
            for(auto num:nums){
                ans+=cnt2[k/__gcd(num,k)];
                if((num*1ll*num)%k==0)ans--;
            }  
            cout<<ans<<endl;
            ans /= 2;
            
            return ans;
    
            
        }
    };