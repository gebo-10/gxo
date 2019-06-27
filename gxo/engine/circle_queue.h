//thread safe circle memery pool
#ifndef CIRCLE_QUEUE
#define CIRCLE_QUEUE

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

	bool write(std::function<void(T *)> write) {
		QueueItem *item = &m_pool[write_sign];
		if (item->state == READ_ABLE)
		{
			return false;
		}
		write(&(item->data));
		item->state = READ_ABLE;
		write_sign += 1;
		write_sign = write_sign % MAX_SIZE;
		return true;
	}

	bool read(std::function<void(T *)> read) {
		QueueItem *item = &(m_pool[read_sign]);
		if (item->state == WRITE_ABLE)
		{
			return false;
		}
		//read(NULL);
		read(&(item->data));
		item->state = WRITE_ABLE;
		read_sign += 1;
		read_sign = write_sign % MAX_SIZE;
		return true;
	}


private:
	QueueItem m_pool[MAX_SIZE];
	int write_sign;
	int read_sign;
};


#endif
