#ifndef LABWORK10_1SUKHARIK_LIB_SHEDULER_H_
#define LABWORK10_1SUKHARIK_LIB_SHEDULER_H_

#include <memory>
#include "iostream"
#include "vector"

class TTaskScheduler {
 private:

  class Rapper {
   public:
    friend class TTaskScheduler;
    int id;
    static int Count;

    Rapper *dependance_for_next = nullptr;
    Rapper *dependance = nullptr;

    virtual void *GetAnwer() = 0;
    virtual void CallF() = 0;

    virtual std::unique_ptr<Rapper> clone() const = 0;

    virtual ~Rapper() = default;
  };

  template<class Lambda, class Param>
  class Task1 : public Rapper {
   public:
    friend class TTaskScheduler;
    std::unique_ptr<Rapper> clone() const override {
      return std::make_unique<Task1>(*this);
    }

    Task1(Lambda& L, Param& p1, Param& p2) : function_(L), parametr1_(p1), parametr2_(p2) {
      Count++;
      id = Count;
      result = 0;
      dependance = nullptr;
      dependance_for_next = nullptr;

    }

    ~Task1() = default;
    void CallF() override {

      if (dependance) {
        parametr2_ = *static_cast<Param *>(dependance->GetAnwer());

      }
      result = function_(parametr1_, parametr2_);

    }

    void *GetAnwer() override {
      return static_cast<void *>(&result);

    }

    Param result;
    Lambda function_;

    Param parametr1_;
    Param parametr2_;

  };

  template<class Lambda, class Param>
  class Task2 : public Rapper {
   public:
    friend class TTaskScheduler;
    std::unique_ptr<Rapper> clone() const override {
      return std::make_unique<Task2>(*this);
    }

    Task2(Lambda& L,Param& p1) :
    function_ (L), parametr1_(p1) {

      result = 0;
      dependance = nullptr;
      dependance_for_next = nullptr;

      Count++;
      id = Count;

    }


    ~Task2() = default;
    void CallF() override {


        if (dependance) {
          parametr1_ = *static_cast<Param *>(dependance->GetAnwer());

        }
        result = function_(parametr1_);


    }

    void *GetAnwer() override {
      return static_cast<void *>(&result);

    }

    Param result;
    Lambda function_;

    Param parametr1_;


  };

  template<class Lambda, class Param>
  class Task3 : public Rapper {
   public:
    friend class TTaskScheduler;
    std::unique_ptr<Rapper> clone() const override {
      return std::make_unique<Task3>(*this);
    }


    Task3(Lambda& L) :
    function_(L) {
        result = 0;
        dependance = nullptr;
        dependance_for_next = nullptr;

        Count++;
        id = Count;

    }

    ~Task3() = default;
    void CallF() override {

        result = function_();


    }

    void *GetAnwer() override {
      return static_cast<void *>(&result);

    }

    Param result;
    Lambda function_;


  };

  std::vector<Rapper *> all_tasks;
 public:

  template<class Lambda, class Param>
  Rapper *add(Lambda L, Param p1, Param p2) {

    Task1<Lambda, Param> *task;
    if (task->Count == 0) {
      all_tasks.push_back(task);
      all_tasks.push_back(task);
    } else {
      all_tasks.push_back(task);
    }

    all_tasks[task->Count - 1] = new Task1<Lambda, Param>(L, p1, p2);
    if (task->Count >= 2 && all_tasks[task->Count - 2]->dependance_for_next) {
      all_tasks[task->Count - 1]->dependance = all_tasks[task->Count - 2]->dependance_for_next;
    }

    return all_tasks[task->Count - 1];

  }
  template<class Lambda, class Param>
  Rapper *add(Lambda L, Param p1) {

    Task2<Lambda, Param> *task;
    if (task->Count == 0) {
      all_tasks.push_back(task);
      all_tasks.push_back(task);
    } else {
      all_tasks.push_back(task);
    }

    all_tasks[task->Count - 1] = new Task2<Lambda, Param>(L, p1);
    if (task->Count >= 2 && all_tasks[task->Count - 2]->dependance_for_next) {
      all_tasks[task->Count - 1]->dependance = all_tasks[task->Count - 2]->dependance_for_next;
    }

    return all_tasks[task->Count - 1];

  }
  template<class Lambda, class Param>
  Rapper *add(Lambda L) {

    Task3<Lambda, Param> *task;
    if (task->Count == 0) {
      all_tasks.push_back(task);
      all_tasks.push_back(task);
    } else {
      all_tasks.push_back(task);
    }

    all_tasks[task->Count - 1] = new Task3<Lambda, Param>(L);
    if (task->Count >= 2 && all_tasks[task->Count - 2]->dependance_for_next) {
      all_tasks[task->Count - 1]->dependance = all_tasks[task->Count - 2]->dependance_for_next;
    }

    return all_tasks[task->Count - 1];

  }
  template<class T>
  T getFutureResult(Rapper *task) {
    all_tasks[task->Count - 1]->dependance_for_next = task;

    return *static_cast<T *>(task->GetAnwer());

  }

  template<class T>
  T getResult(Rapper *task) {

    return *static_cast<T *>(task->GetAnwer());

  }

  void executeAll() {
    for (int i = 0; i < all_tasks.size() - 1; i++) {
      all_tasks[i]->CallF();
//      std::cout << all_tasks[i]->id << " " << *static_cast<float *>(all_tasks[i]->GetAnwer()) << "\n";

    }

  }

  TTaskScheduler operator=(TTaskScheduler const& other) {
    TTaskScheduler tmp(other);
    std::swap(this->all_tasks, tmp.all_tasks);
    return *this;
  }

};
int TTaskScheduler::Rapper::Count = 0;

#endif //LABWORK10_1SUKHARIK_LIB_SHEDULER_H_
