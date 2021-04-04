/*  EL2208 Praktikum Pemecahan Masalah dengan C 2020/2021
*   Modul            : 7
*   Percobaan        : -
*   Hari dan Tanggal : -
*   Nama (NIM)       : - 
*   Asisten (NIM)    : Andhika Rahadian (13218030)
*   Nama File        : -
*   Deskripsi        : Program Stack Playlist Spotipi
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song
{
    char author[25];
    char songName[50];
    int nowPlayingId;
};

typedef struct node_stack
{
    struct node_stack *nextNode;
    struct song songData;

} node;

typedef struct stack_playlist
{
    struct node_stack *top;

} stack;
int isEmptyPlaylist(stack *playlist)
{
    return (playlist->top == NULL ? 1 : 0);
}
void push(stack *playlist, struct song _songData)
{
    node *newNode;
    newNode = malloc(sizeof(struct node_stack));
    newNode->songData = _songData;
    newNode->nextNode = playlist->top;
    playlist->top = newNode;
}
void showPlaylist(stack *playlist, int id)
{

    node *tmp;
    int i = 0;
    tmp = playlist->top;

    printf("\nNow Playing:\n");
    if (isEmptyPlaylist(playlist))
    {
        printf("Playlist kosong! Tambahkan lagu!\n");
        return;
    }
    // Reverse stack Agar User Friendly
    stack *reversed_display;
    reversed_display = malloc(sizeof(stack *));
    reversed_display->top = NULL;
    while (tmp != NULL)
    {
        push(reversed_display, tmp->songData);
        tmp = tmp->nextNode;
    }

    // Traverse Reversed Stack, Dan Tampilkan
    tmp = reversed_display->top;
    while (tmp != NULL)
    {
        if (i == id)
        {
            printf("-> %s by %s",
                   tmp->songData.author,
                   tmp->songData.songName);
        }
        else
        {
            printf("   %s by %s",
                   tmp->songData.author,
                   tmp->songData.songName);
        }
        tmp = tmp->nextNode;
        i++;
    }
}

void pop(stack *playlist)
{
    node *tmp;
    tmp = playlist->top;
    playlist->top = tmp->nextNode;

    free(tmp);
}

int main()
{
    stack *currPlaylist;
    char *token;
    struct song songBuf;
    char str[75];
    currPlaylist = (stack *)malloc(sizeof(stack));

    // PENTING!!! INISIALISASI
    currPlaylist->top = NULL;

    char cmd = 'X';
    int songId = 0;
    int nowIndex = -1;
    int numOfSong = 0;

    while (cmd != 'E')
    {
        showPlaylist(currPlaylist, nowIndex);

        printf("\nMasukkan Perintah: ");
        scanf("%c", &cmd);

        // PENTING, BUAT PAKE FGETS
        getchar();

        // ADD LAGU
        if (cmd == 'A')
        {
            printf("Masukkan Nama Lagu dan Penyanyi: ");
            scanf("%[^\n]s",str);
            char ch = '\n';
            strncat(str, &ch, 1);

            token = strtok(str, ",");
            strcpy(songBuf.author, token);
            token = strtok(NULL, ",");
            strcpy(songBuf.songName, token);
            songBuf.nowPlayingId = songId;
            songId++;
            push(currPlaylist, songBuf);

            // Clear buffer
            getchar();
        }

        // NEXT
        if (cmd == 'N')
        {
            nowIndex++;
        }

        // PREVIOUS
        if (cmd == 'P')
        {
            nowIndex--;
        }

        // RESTART to 0
        if (cmd == 'R')
        {
            nowIndex = 0;
        }
        // Delete Top of the Playlist
        if (cmd == 'D')
        {
            pop(currPlaylist);
            songId--;
        }
    }
    return 0;
}
