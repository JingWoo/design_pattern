#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct game {
    void (*initialize)();
    void (*play)();
    void (*finish)();
};

void play_game(struct game *game)
{
    assert(game != NULL);
    game->initialize();
    game->play();
    game->finish();
}

static void game_a_initialize()
{
    printf("%s\n", __FUNCTION__);
}

static void game_a_play()
{
    printf("%s\n", __FUNCTION__);
}

static void game_a_finish()
{
    printf("%s\n", __FUNCTION__);
}

static void game_b_initialize()
{
    printf("%s\n", __FUNCTION__);
}

static void game_b_play()
{
    printf("%s\n", __FUNCTION__);
}

static void game_b_finish()
{
    printf("%s\n", __FUNCTION__);
}

struct game *game_init(void (*initialize)(), void (*play)(), void (*finish)())
{
    struct game *game = (struct game *)calloc(1, sizeof(struct game));
    assert(game != NULL);
    game->initialize = initialize;
    game->play = play;
    game->finish = finish;

    return game;
}

int main()
{
    struct game *game_a = game_init(game_a_initialize, game_a_play, game_a_finish);
    play_game(game_a);
    free(game_a);

    struct game *game_b = game_init(game_b_initialize, game_b_play, game_b_finish);
    play_game(game_b);
    free(game_b);

    exit(EXIT_SUCCESS);
}
