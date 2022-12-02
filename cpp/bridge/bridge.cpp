
#include <stdio.h>
#include <list>
#include <vector>
#include <map>

using namespace std;

class StorageImpl {
public:
	virtual float get(int index) = 0;
	virtual void set(int index, float value) = 0;
	virtual void push_back(float value) = 0;
	virtual void push_front(float value) = 0;
	virtual int size() = 0;
	virtual ~StorageImpl() { }
};

class ListStorageImpl : public StorageImpl {
private:
	list<float> values;
public:
	float get(int index) override {
		for (list<float>::iterator i = values.begin(); i != values.end(); i++)
			if (index == 0)
				return *i;
			else
				index--;
		return 0;
	}
	void set(int index, float value) override {
		for (list<float>::iterator i = values.begin(); i != values.end(); i++)
			if (index == 0) {
				*i = value;
				break;
			}
			else
				index--;
	}
	void push_back(float value) override {
		values.push_back(value);
	}
	void push_front(float value) override {
		values.push_front(value);
	}
	int size() override {
		return values.size();
	}
};

class VectorStorageImpl : public StorageImpl {
private:
	vector<float> values;
public:
	float get(int index) override {
		return values[index];
	}
	void set(int index, float value) override {
		values[index] = value;
	}
	void push_back(float value) override {
		values.push_back(value);
	}
	void push_front(float value) override {
		values.insert(values.begin(), value);
	}
	int size() override {
		return values.size();
	}
};

class Storage {
protected:
	StorageImpl *impl;
	map<string, int> ops;
public:
	Storage() {
		impl = new ListStorageImpl();
		ops["getset"] = 0;
		ops["pushback"] = 0;
		ops["pushfront"] = 0;
	}
	float get(int index) {
		ops["getset"]++;
		relocate();
		return impl->get(index);
	}
	void set(int index, float value) {
		ops["getset"]++;
		relocate();
		impl->set(index, value);
	}
	void push_back(float value) {
		ops["pushback"]++;
		relocate();
		impl->push_back(value);
	}
	void push_front(float value) {
		ops["pushfront"]++;
		relocate();
		impl->push_front(value);
	}
	int size() {
		return impl->size();
	}
	void relocate();
	virtual ~Storage() {
		delete impl;
	}
};

void Storage::relocate() {
	if (ops["getset"] > ops["push_front"] && 
			dynamic_cast<ListStorageImpl*>(impl) != nullptr) {
		printf("Relocating List to Vector\n");
		StorageImpl *new_impl = new VectorStorageImpl;
		for (int i = 0; i < impl->size(); i++)
			new_impl->push_back(impl->get(i));
		delete impl;
		impl = new_impl;
	}

	if (ops["push_front"] > ops["getset"] && 
			dynamic_cast<VectorStorageImpl*>(impl) != nullptr) {
		printf("Relocating Vector to List\n");
		StorageImpl *new_impl = new ListStorageImpl;
		for (int i = 0; i < impl->size(); i++)
			new_impl->push_back(impl->get(i));
		delete impl;
		impl = new_impl;
	}
}


class OrderedStorage : public Storage {
public:
	void sort() {
		for (int i = 0; i < impl->size(); i++)
			for (int j = i + 1; j < impl->size(); j++)
				if (impl->get(i) > impl->get(j)) {
					float xi = get(i);
					float xj = get(j);
					set(i, xj);
					set(j, xi);
				}
	}
};

void main() {
	{ 
		OrderedStorage storage;

		printf("Inserting values\n");
		for (int i = 0; i < 5; i++)
			storage.push_front(rand() % 100);

		printf("Accessing values twice\n");
		for (int i = 0; i < storage.size(); i++)
			printf("%.1f\n", storage.get(i));
		for (int i = 0; i < storage.size(); i++)
			printf("%.1f\n", storage.get(i));

		printf("Inserting values twice\n");
		for (int i = 0; i < 5; i++)
			storage.push_front(rand() % 100);
		for (int i = 0; i < 5; i++)
			storage.push_front(rand() % 100);

		printf("Sorting values\n");
		storage.sort();

		printf("Accessing values once\n");
		for (int i = 0; i < storage.size(); i++)
			printf("%.1f\n", storage.get(i));
	}
	system("pause");
}