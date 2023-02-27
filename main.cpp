#include <iostream>
#include "main.h"
#include "sha256.h"
#include "ctime"
#include "string.h"
#include "math.h"
#include "fastcmp.h"
#include "mingw.thread.h"
//#include "cores.h"

using namespace std;

// cls && g++ -Wall -Wextra -o sha256.o main.cpp main.h sha256.cpp sha256.h && sha256.o
// g++ -Wall -Wextra -o sha256.o main.cpp mingw.thread.h main.h sha256.cpp sha256.h fastcmp.h

/*struct thread_data {
    const char* set;
    const short set_len;
    const char* hash;
    const unsigned short id;
    const short step;
    int *c;
    bool *finished;
};*/

void brute(const char* set, const unsigned int set_len, const char* hash, const short id, const short step, int *c, bool *finished){
    cout << "started thread: " << id << endl;

    /*struct thread_data *args = (struct thread_data*) threadarg;
    const unsigned int set_len = args->set_len;
    const char* set = args->set;
    const char* hash = args->hash;
    int *c = args->c;
    const short step = args->step;
    bool *finished = args->finished;*/

    char tmp_hash[65] = {};
    short counter[32] = {0};
    counter[0] = id;
    short c_len = 1;
    while (true){
        for (int i = c_len - 1; i >= 0; --i) {
            if (counter[i] >= set_len){
                const short d = counter[i] / set_len;
                counter[i] %= set_len;
                if(!i){
                    for (int a = c_len-1; a >= 0; --a){
                        counter[a+1] = counter[a];counter[a]=0;}
                    c_len++;
                    counter[0] = d;
                    //if(!id) cout << "\rbruteforcing at: " << c_len << " characters!";
                } else
                    counter[i-1] += d;
            }
        }
        //if(id==7){cout << " ??";for (int i = 0; i < c_len; ++i){cout << counter[i]<<',';}cout<<endl;}

        unsigned char pw[c_len];
        for (int i = 0; i < c_len; ++i)//{
            pw[i] = set[counter[i]];//cout << counter[i]<<",";}cout<<endl;
        sha256(pw,c_len,tmp_hash);
        if(!fastcmp(tmp_hash,hash)){
            cout << endl << "found: " << string((char*)(pw), c_len) << " | hash: " << string(tmp_hash,65) << " | thread id: " << id << endl;
            *finished = true;
            break;
        }
        counter[c_len-1]+=step;
        //for (int i = 0; i < c_len; ++i){cout << counter[i]<<",";}cout<<"=="<<endl;
        (*c)++;
    }
}

const chrono::milliseconds waitTime = chrono::milliseconds(50);
int main( int argc, char** argv) {
    if(argc < 2 || argc > 3){
        cout << "usage: sha256.o <sha256 hash> OR sha256.o <sha256 hash> <cores>" << endl;
        return -1;
    }
    short threadCount = 0;
    if(argc == 3) threadCount = atoi(argv[2]);
    else threadCount = thread::hardware_concurrency();

    if(threadCount == 0){
        cout << "couldn\'t automatically detect or read core amount.. please specify the amount within the command" << endl;
        return -1;
    }

    bool finished = false;
    int count = 0;
    clock();
    cout << "bruteforcing the following hash: " << string(argv[1],64) << endl;
    cout << "threads: " << threadCount << endl;
    for (unsigned short i = 0; i < threadCount; ++i) {
        thread _t(brute,SET_NUM,SET_NUM_LEN,argv[1],i,threadCount,&count,&finished);
        _t.detach();
    }


    while (!finished) this_thread::sleep_for(waitTime);
    clock_t run_time = clock();
    cout << "hashses "<<count<<" | hashrate "<< (count/(run_time/1000.0)) <<"H/s >" << (count/(run_time/1000.0))/1000 <<"kH/s > "<< round((count/(run_time/1000.0))/1000)/1000 << "MH/s" << endl;
    cout << "time: " << run_time << "ms > " << run_time/1000.0 << "s > " << run_time/60000 <<"m" <<endl;
    exit(0);
    return 0;
}
