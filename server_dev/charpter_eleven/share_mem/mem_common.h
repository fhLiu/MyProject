#pragma once

const int MAX_TEXT_SIZE = 2048;
const int shm_key_s = 1234;

struct SharedUseSt
{
    int written;
    char text[MAX_TEXT_SIZE];
};
