#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Cell {
    struct Cell* adjacent_cells[4];
    int visited;
};

enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

struct Grid {
    struct Cell** cells;
    int width;
    int height;
};


struct Grid* create_grid(int width, int height) {
    struct Grid* grid = malloc(sizeof(struct Grid));
    if(!grid){
        return NULL;
    }
    grid->width = width;
    grid->height = height;
    grid->cells = malloc(sizeof(struct Cell*) * height);
    for (int i = 0; i < height; i++) {
        grid->cells[i] = malloc(sizeof(struct Cell) * width);
        for (int j = 0; j < width; j++) {
            for (int d = 0; d < 4; d++) {
                grid->cells[i][j].adjacent_cells[d] = NULL;
            }
            grid->cells[i][j].visited = 0;
        }
    }
    return grid;
}

void dfs(struct Grid* grid, int i, int j) {
    grid->cells[i][j].visited = 1;

    int directions[4] = {NORTH, SOUTH, WEST, EAST};
    for (int k = 3; k > 0; k--) {
        int r = rand() % (k + 1);
        int tmp = directions[k];
        directions[k] = directions[r];
        directions[r] = tmp;
    }

    for (int k = 0; k < 4; k++) {
        int ni, nj;
        if (directions[k] == NORTH) { ni = i-1; nj = j;   }
        if (directions[k] == SOUTH) { ni = i+1; nj = j;   }
        if (directions[k] == WEST)  { ni = i;   nj = j-1; }
        if (directions[k] == EAST)  { ni = i;   nj = j+1; }

        if (ni >= 0 && ni < grid->height && nj >= 0 && nj < grid->width
            && !grid->cells[ni][nj].visited) {

            grid->cells[i][j].adjacent_cells[directions[k]] = &grid->cells[ni][nj];
            grid->cells[ni][nj].adjacent_cells[directions[k] ^ 1] = &grid->cells[i][j];

            dfs(grid, ni, nj);
        }
    }
}

    void print_grid(struct Grid* grid) {
        for (int i = 0; i < grid->height; i++) {
            // Passage 1 : murs horizontauxx²
            for (int j = 0; j < grid->width; j++) {
                printf("+");
                if (grid->cells[i][j].adjacent_cells[NORTH] == NULL) {
                    printf("--");
                } else {
                    printf("  ");
                }
            }
            printf("+\n");

            // Passage 2 : murs verticaux
            for (int j = 0; j < grid->width; j++) {
        if (grid->cells[i][j].adjacent_cells[WEST] == NULL) {
            printf("|");
        } else {
            printf(" ");
        }
        printf("  ");
    }
    printf("|\n");
            
        }
        for (int j = 0; j < grid->width; j++) {
            printf("+--");
        }
        printf("+\n");
    }

int main(void) {
    srand(time(NULL));
    struct Grid* grid = create_grid(5, 5);
    dfs(grid, 0, 0);
    print_grid(grid);
}