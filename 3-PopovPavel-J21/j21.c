#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_MAP_SIZE 3751711
#define HASH_MAP_STEP 7
#define BUF_SIZE 128

typedef enum {
	WAS_NOT_USED,
	FREE,
	BUSY
} Status;

typedef struct {
	char* str;
	Status status;
} Node;

typedef struct {
	Node* data;
	size_t size;
	size_t step;
} HashTable;

size_t Hash(const char* str, const size_t hashTableSize) {
	const int c = 21;
	size_t hash = 0;
	for (int i = 0; str[i]; i++) {
		hash = c * hash + str[i];
	}
	return hash % hashTableSize;
}

static size_t FindIndex(const HashTable* hashTable, const char* str) {
	size_t index = Hash(str, hashTable->size);
	const size_t indexStart = index;
	while (!hashTable->data[index].str || hashTable->data[index].status != BUSY || strcmp(str, hashTable->data[index].str)) {
		index = (index + hashTable->step) % hashTable->size;
		if (hashTable->data[index].status == WAS_NOT_USED || index == indexStart) {
			return hashTable->size;
		}
	}
	return index;
}

bool Find(const HashTable* hashTable, const char* str) {
	return FindIndex(hashTable, str) != hashTable->size;
}

HashTable HashTableInit(const size_t size, const size_t step) {
	HashTable res;
	res.step = step;
	res.data = (Node*)malloc(size * sizeof(Node));
	if (!res.data) {
		exit(-1);
	}
	res.size = res.data ? size : 0;
	for (size_t i = 0; i < res.size; i++) {
		res.data[i].str = NULL;
		res.data[i].status = WAS_NOT_USED;
	}
	return res;
}

bool Insert(HashTable* hashTable, const char* str) {
	size_t index = Hash(str, hashTable->size);
	const size_t indexStart = index;
	long long firstDeleted = -1;
	while (hashTable->data[index].str) {
		if (!strcmp(hashTable->data[index].str, str) && hashTable->data[index].status == BUSY) {
			return false;
		}
		if (hashTable->data[index].status == FREE && firstDeleted == -1) {
			firstDeleted = index;
		}
		index = (index + hashTable->step) % hashTable->size;
		if (index == indexStart) {
			return false;
		}
	}
	if (firstDeleted != -1) {
		free(hashTable->data[firstDeleted].str);
		index = (size_t)firstDeleted;
	}
	hashTable->data[index].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!hashTable->data[index].str) {
		return false;
	}
	strcpy(hashTable->data[index].str, str);
	hashTable->data[index].status = BUSY;
	return true;
}

void Remove(HashTable* hashTable, const char* str) {
	size_t index = FindIndex(hashTable, str);
	if (index == hashTable->size) {
		return;
	}
	hashTable->data[index].status = FREE;
}

void Destroy(HashTable* hashTable) {
	for (size_t i = 0; i < hashTable->size; i++) {
		if (hashTable->data[i].str) {
			free(hashTable->data[i].str);
		}
	}
	free(hashTable->data);
	hashTable->data = NULL;
	hashTable->size = 0;
}

int main() {
	HashTable map = HashTableInit(HASH_MAP_SIZE, HASH_MAP_STEP);
	if (map.size == 0) {
		return -1;
	}
	char buf[BUF_SIZE] = { 0 };
	char c = 0;
	char str[BUF_SIZE] = { 0 };
	while (fgets(buf, BUF_SIZE, stdin)) {
		sscanf(buf, "%c %s", &c, &str);
		switch (c) {
		case 'a':
			Insert(&map, str);
			break;
		case 'r':
			Remove(&map, str);
			break;
		case 'f':
			printf("%s\n", Find(&map, str) ? "yes" : "no");
			break;
		default:
			Destroy(&map);
			return 0;
		}
	}
	Destroy(&map);
	return 0;
}