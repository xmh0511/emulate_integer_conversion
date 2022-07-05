#include <iostream>
#include <climits>
#include <type_traits>
template<class T>
struct convert_from{
    T source_;
    template<class U>
    constexpr U to(){
      constexpr int dest_width = CHAR_BIT * sizeof(U);
      constexpr int src_width = CHAR_BIT * sizeof(T);
      long long int max = 1;
      long long int min = 0;
      long long int base = 1;
      for(int c = 0; c< dest_width;c++){
          base*=2;
      }
      if constexpr(std::is_unsigned_v<U>){
        for(int i = 0; i< dest_width;i++){
            max*=2;
        }
      }else{
        min = 1;
        for(int i = 0; i< dest_width -1;i++){
            max*=2;
            min*=2;
        }
        min = -min;
      }
       max-=1;
       //b = source_ - k*2^src_width
       // min <= source_ - k*2^src_width <= max
       // min-source_ <= - k*2^src_width <= max-source_
       // source_ - max <= k*base <= source_ - min
       double lower = (source_ - max) / base;
       double upper = (source_ - min) /base;
       for(double k = lower; k <=upper;k++ ){
           long long int v = source_ - k*base;
           if(v >= min && v<=max)
           return  v;
       }
       return 0;
    }
};

int main(){
    constexpr auto c = convert_from<int>{-1000045}.to<short>();
    std::cout<< c << std::endl;
    std::cout<<(short)-1000045<<std::endl;
}
