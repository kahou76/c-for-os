const int NUM_KIDS = 3;
const int MSG_SIZE = 16;

int main() {
    //READ WRTIE
    int fd[NUM_KIDS][2];
    pid_t pid[NUM_KIDS];

    cerr << "Start pid: " << getpid() << endl;

    for (int i = 0; i < NUM_KIDS; i++ ) {
        pipe(fd[i]);
        pid[i] = fork(); // Assume no error
        if (pid[i] == 0) {
            cerr << "i = " << i << ", pid: " << getpid() << endl;
            //close read
            close(fd[i][0]);
            //open write
            dup2(fd[i][1], 1);
            cout << getpid() << "-" << i << endl;
            exit(0);
        } else {
            //close write
            close(fd[i][1]);
        }
    }
    for (int i = 0; i < NUM_KIDS; i++ ) {
        char msg[MSG_SIZE];
        read(fd[i][0], msg, MSG_SIZE);
        cout << "msg: " << msg << endl;
        waitpid(pid[i], NULL, 0); // Block and wait
        close(fd[i][0]);
    }
}