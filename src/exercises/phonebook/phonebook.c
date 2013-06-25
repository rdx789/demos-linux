#include <stdio.h> // for printf(3)
#include <stdlib.h> // for EXIT_SUCCESS, malloc(3)
#include <string.h>	// for strncpy(3), strcmp(3)
#include <us_helper.h>	// for CHECK_INT()

const int MAX_SIZE_OF_NAME=20;
const int MAX_SIZE_OF_PHONE=20;
const int MAX_ENTRIES_IN_PHONEBOOK=100;

struct phone_entry {
	char name[20];
	char phone[20];
	int used;
};

void phone_entry_init(struct phone_entry* pe) {
	pe->used=0;
}

int over=0;

int show_menu() {
	int result;
	do {
		printf("here is your menu....\n");
		printf("1) add an entry (name and phone)\n");
		printf("2) delete an entry (by name)\n");
		printf("3) print the phonebook\n");
		printf("4) exit\n");
		CHECK_INT(scanf("%d", &result),1);
	} while(result<1 || result>4);
	return result;
}

int main(int argc, char** argv, char** envp) {
	int i;
	struct phone_entry* phonebook;
	phonebook=malloc(sizeof(struct phone_entry)*MAX_ENTRIES_IN_PHONEBOOK);
	for(i=0;i<MAX_ENTRIES_IN_PHONEBOOK;i++) {
		phone_entry_init(phonebook+i);
		//(phonebook+i)->used=0;
		//phonebook[i].used=0;
		//*(phonebook+i).used=0;
	}
	while(!over) {
		int selection=show_menu();
		switch(selection) {
			case 1:
				printf("adding an entry\n");
				break;
			case 2:
				printf("deleting an entry\n");
				break;
			case 3:
				printf("printing the phonebook\n");
				break;
			case 4:
				printf("terminating\n");
				over=1;
				break;
		}
	}

	// release the memory
	free(phonebook);
	return EXIT_SUCCESS;
}
