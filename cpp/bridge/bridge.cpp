
#include <stdio.h>
#include <list>
#include <vector>

using namespace std;

class StorageImpl
{
public:
	virtual float get(int index) = 0;
	virtual void set(int index, float value) = 0;
	virtual void insert(float value) = 0;
	virtual int size() = 0;
	virtual ~StorageImpl()
	{
	}
};

class ListStorageImpl : public StorageImpl
{
private:
	list<float> values;
public:
	float get(int index) override
	{
		for (list<float>::iterator i = values.begin(); i != values.end(); i++)
			if (index == 0)
				return *i;
			else
				index--;
		return 0;
	}
	void set(int index, float value) override
	{
		for (list<float>::iterator i = values.begin(); i != values.end(); i++)
			if (index == 0)
			{
				*i = value;
				break;
			}
			else
				index--;
	}
	void insert(float value) override
	{
		values.insert(values.begin(), value);
	}
	int size() override
	{
		return values.size();
	}
};

class VectorStorageImpl : public StorageImpl
{
private:
	vector<float> values;
public:
	float get(int index) override
	{
		return values[index];
	}
	void set(int index, float value) override
	{
		values[index] = value;
	}
	void insert(float value) override
	{
		values.insert(values.begin(), value);
	}
	int size() override
	{
		return values.size();
	}
};

class Storage
{
protected:
	StorageImpl *impl;
	int getset_cnt, insert_cnt;
public:
	Storage()
	{
		getset_cnt = 0;
		insert_cnt = 0;
		impl = new ListStorageImpl();
	}
	float get(int index)
	{
		getset_cnt = getset_cnt + 1;
		relocate();

		return impl->get(index);
	}
	void set(int index, float value)
	{
		getset_cnt = getset_cnt + 1;
		relocate();

		impl->set(index, value);
	}
	void insert(float value)
	{
		insert_cnt = insert_cnt + 1;
		relocate();

		impl->insert(value);
	}
	int size()
	{
		return impl->size();
	}
	void relocate()
	{
		if (getset_cnt > insert_cnt && dynamic_cast<ListStorageImpl*>(impl) != nullptr)
		{
			printf("Relocating List to Vector\n");
			StorageImpl *new_impl = new VectorStorageImpl;
			for (int i = impl->size() - 1; i >= 0; i--)
				new_impl->insert(impl->get(i));
			delete impl;
			impl = new_impl;
		}

		if (insert_cnt > getset_cnt && dynamic_cast<VectorStorageImpl*>(impl) != nullptr)
		{
			printf("Relocating Vector to List\n");
			StorageImpl *new_impl = new ListStorageImpl;
			for (int i = impl->size() - 1; i >= 0; i--)
				new_impl->insert(impl->get(i));
			delete impl;
			impl = new_impl;
		}
	}
	virtual ~Storage()
	{
		delete impl;
	}
};

class OrderedStorage : public Storage
{
public:
	void sort()
	{
		for (int i = 0; i < impl->size(); i++)
			for (int j = i + 1; j < impl->size(); j++)
				if (impl->get(i) > impl->get(j))
				{
					float xi = get(i);
					float xj = get(j);
					set(i, xj);
					set(j, xi);
				}
	}
};


void main()
{
	{ OrderedStorage storage;

	printf("Inserting values\n");
	for (int i = 0; i < 5; i++)
		storage.insert(rand() % 100);

	printf("Accessing values twice\n");
	for (int i = 0; i < storage.size(); i++)
		printf("%.1f\n", storage.get(i));
	for (int i = 0; i < storage.size(); i++)
		printf("%.1f\n", storage.get(i));

	printf("Inserting values twice\n");
	for (int i = 0; i < 5; i++)
		storage.insert(rand() % 100);
	for (int i = 0; i < 5; i++)
		storage.insert(rand() % 100);

	printf("Sorting values\n");
	storage.sort();

	printf("Accessing values once\n");
	for (int i = 0; i < storage.size(); i++)
		printf("%.1f\n", storage.get(i));
	}
	system("pause");
}