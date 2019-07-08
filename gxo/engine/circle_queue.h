//thread safe circle memery pool
#ifndef CIRCLE_QUEUE
#define CIRCLE_QUEUE
#include<atomic>
template<class T, size_t MAX_SIZE = 3>
class CircleQueue
{
private:
	enum BuffState {
		WRITE_ABLE = 0,
		READ_ABLE
	};
	struct QueueItem {
		BuffState state;
		T data;
	};
public:
	CircleQueue()
	{
		reset();
	}

	~CircleQueue() {}

	void reset() {
		//reset thread not safe !!!
		write_sign = 0;
		read_sign = 0;
		for (auto item: m_pool)
		{
			item.state = WRITE_ABLE;
		}
	}

	bool push(std::function<void(T *)> fun) {
		QueueItem *item = &m_pool[write_sign];
		if (item->state == READ_ABLE)
		{
			return false;
		}
		fun(&(item->data));
		item->state = READ_ABLE;
		write_sign ++;
		write_sign = write_sign % MAX_SIZE;
		return true;
	}

	bool pop(std::function<void(T *)> fun) {
		QueueItem *item = &(m_pool[read_sign]);
		if (item->state == WRITE_ABLE)
		{
			return false;
		}
		fun(&(item->data));
		item->state = WRITE_ABLE;
		read_sign ++;
		read_sign = read_sign % MAX_SIZE;
		return true;
	}

	//bool write_sync(std::function<void(T *)> fun) {
	//	QueueItem *item = &m_pool[write_sign];
	//	if (item->state == READ_ABLE)
	//	{
	//		return false;
	//	}
	//	while(item->state == READ_ABLE)

	//	fun(&(item->data));
	//	item->state = READ_ABLE;
	//	write_sign++;
	//	write_sign = write_sign % MAX_SIZE;
	//	return true;
	//}

	//void read_sync(std::function<void(T *)> fun) {
	//	QueueItem *item = &(m_pool[read_sign]);
	//	if (item->state == WRITE_ABLE)
	//	{
	//		return false;
	//	}
	//	fun(&(item->data));
	//	item->state = WRITE_ABLE;
	//	read_sign++;
	//	read_sign = read_sign % MAX_SIZE;
	//	return true;
	//}


private:
	int write_sign;
	int read_sign;
	//std::atomic<int> write_sign;
	//std::atomic<int> read_sign;
	QueueItem m_pool[MAX_SIZE];
};


#endif
