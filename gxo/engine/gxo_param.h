#ifndef GXO_PARAM_H
#define GXO_PARAM_H
#include"gxo_type.h"
namespace gxo {

	class Params {
	private:
		std::vector<std::any> data_;
	public:
		Params() {}
		~Params() {}
		size_t size() const { return data_.size(); }
		void clear() { data_.clear(); }
		bool empty() { return data_.empty(); }
		template <typename T>
		bool push_param(T t) {
			std::any value = t;
			data_.push_back(value);
			return true;
		}

		template <typename T>
		bool pop_param(T& t) {
			assert(0 < size());
			t = std::any_cast<T>(data_.back());
			data_.pop_back();
			return true;
		}

		template <typename T>
		bool get_param(unsigned int i, T& t) const {
			assert(i < size());
			t = std::any_cast<T>(data_.at(i));
			return true;
		}

		template <typename T>
		T get_param(unsigned int i) {
			assert(i < size());
			return std::any_cast<T>(data_.at(i));
		}
	};

	////////////////////////////////////////////////////////////////
	template <typename Head, typename... Args>
	class GenParamTuple {
	public:
		static inline std::tuple<Head, Args...> Run(int index, Params& p) {
			std::tuple<Args...> t = GenParamTuple<Args...>::Run(index + 1, p);
			Head pn;
			p.get_param(index, pn);
			return std::tuple_cat(std::make_tuple(pn), t);
		}
	};

	template <typename Last>
	class GenParamTuple<Last> {
	public:
		static inline std::tuple<Last> Run(int index, Params& p) {
			Last pn;
			p.get_param(index, pn);
			return std::make_tuple(pn);
		}
	};

	struct Callable {
		Callable() {}
		~Callable() {}
		virtual void operator()(Params& p) = 0;
	};
	typedef std::shared_ptr<Callable> CallablePtr;

	template <typename... Args>
	struct CallObject : public Callable {
		std::function<void(Args...)> fun;
		void operator()(Params& p) {
			auto t_p = GenParamTuple<Args...>::Run(0, p);
			std::apply(fun, t_p);
		}
	};

	template <>
	struct CallObject<void> : public Callable {
		std::function<void(void)> fun;
		void operator()(Params& p) { fun(); }
	};
}
#endif // !GXO_PARAM_H