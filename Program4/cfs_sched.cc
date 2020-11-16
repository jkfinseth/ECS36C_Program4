#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "multimap.h"

class Task {
 public:
  // Constructor
  Task(char identifier, unsigned int start_time, unsigned int duration);

  // Operator
  friend bool operator<(const Task& taskleft, const Task& taskright);
  friend bool operator>(const Task& taskleft, const Task& taskright);
  friend bool operator==(const Task& taskleft, const Task& taskright);

  // Edit operators
  void SetVruntime(int val);
  void IncreaseRuntime();
  void DecreaseDuration();
  void Initialize();

  // Functions
  bool IsFinished();
  char ReturnIdentifier();
  bool IsInitialized();
  int ReturnVruntime();
  unsigned int ReturnStartTime();

 private:
  char identifier;
  unsigned int start_time;
  unsigned int duration;
  int min_vruntime;
  bool initialized;

  // Helper Function
  void SetMinVruntime(int val);
  void SwitchComplete();
  int MinVruntime();
  void DurationDecrease();
  char Identifier();
  void UpdateInitialize();
  bool ReturnInitialized();
  unsigned int StartTime();
};

Task::Task(char identifier, unsigned int start_time, unsigned int duration):
identifier(identifier), start_time(start_time), duration(duration),
min_vruntime(0), initialized(false) {
}

bool operator<(const Task& taskleft, const Task& taskright) {
  if (taskleft.min_vruntime < taskright.min_vruntime)
    return true;
  if (taskleft.min_vruntime == taskright.min_vruntime) {
    if (taskleft.identifier < taskright.min_vruntime)
      return true;
  }
  return false;
}

bool operator>(const Task& taskleft, const Task& taskright) {
  if (taskleft.min_vruntime > taskright.min_vruntime)
    return true;
  if (taskleft.min_vruntime == taskright.min_vruntime) {
    if (taskleft.identifier > taskright.identifier)
      return true;
  }
  return false;
}

bool operator==(const Task& taskleft, const Task& taskright) {
  if (taskleft.min_vruntime == taskright.min_vruntime)
    return true;
  return false;
}

void Task::SetMinVruntime(int val) {
  min_vruntime = val;
}

void Task::SetVruntime(int val) {
  SetMinVruntime(val);
}

int Task::MinVruntime() {
  return min_vruntime;
}

void Task::IncreaseRuntime() {
  SetVruntime(MinVruntime()+1);
}

void Task::DurationDecrease() {
  duration--;
}

void Task::DecreaseDuration() {
  DurationDecrease();
}

bool Task::IsFinished() {
  if (duration == 0)
    return true;
  return false;
}

char Task::Identifier() {
  return identifier;
}

char Task::ReturnIdentifier() {
  return Identifier();
}

void Task::UpdateInitialize() {
  initialized = true;
}

void Task::Initialize() {
  UpdateInitialize();
}

bool Task::ReturnInitialized() {
  return initialized;
}

bool Task::IsInitialized() {
  return ReturnInitialized();
}

int Task::ReturnVruntime() {
  return MinVruntime();
}

unsigned int Task::StartTime() {
  return start_time;
}

unsigned int Task::ReturnStartTime() {
  return StartTime();
}

bool CompareTaskPointer(Task* a, Task*b) {
  if (a->ReturnStartTime() > b->ReturnStartTime())
    return false;
  if (a->ReturnStartTime() == b->ReturnStartTime()) {
    if (a->ReturnIdentifier() > b->ReturnIdentifier()) {
      return false;
    } else {
      return true;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  std::vector<Task*> tasks;
  Multimap<int, Task*>  timeline;
  int min_vruntime = 0;
  int tasks_running = 0;

  // Error check to ensure the user is including inputs correctly
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <task_file.dat>" << std::endl;
    exit(1);
  }

  // Begin reading in file
  std::ifstream input;
  std::string line_contents = "";
  std::vector<std::string*> file_contents;

  input.open(argv[1]);

  // Make sure can open file
  if (!input) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    exit(1);
  }

  // Store file in a vector of Tasks
  while (getline(input, line_contents)) {
    if (line_contents.length() != 0) {
      // Create tasks using input
      std::istringstream content_transfer(line_contents);
      char identifier;
      unsigned int start_time;
      unsigned int duration;

      content_transfer >> identifier >> start_time >> duration;

      Task* temp = new Task (identifier, start_time, duration);
      tasks.push_back(temp);
    }
  }

  // Sort vector and store the pointers in tasks
  std::sort(tasks.begin(), tasks.end(), CompareTaskPointer);

  // Close the file stream
  input.close();

  unsigned int tick = 0;
  unsigned int counter = 0;
  unsigned int i;
  bool edited;
  int temp_min;
  Task* temp_task;

  // Begin intilizing timeline
  while (tasks.size() != 0) {
    // Check for tasks that can be loaded
    if (tasks.size() > counter) {
      while (tasks[counter]->ReturnStartTime() == tick) {
        tasks[counter]->SetVruntime(min_vruntime);
        timeline.Insert(min_vruntime, tasks[counter]);
        tasks[counter]->Initialize();
        counter++;
        tasks_running++;
        if (!(tasks.size() > counter))
          break;
        }
      }

    // Update min_vruntime
    temp_min = min_vruntime;
    edited = false;
    for (i=0; i < tasks.size(); i++) {
      if (tasks[i]->IsInitialized()) {
        if (!edited) {
          temp_min = tasks[i]->ReturnVruntime();
          edited = true;
        } else {
          if (tasks[i]->ReturnVruntime() < temp_min)
            temp_min = tasks[i]->ReturnVruntime();
        }
      }
    }

    if (temp_min > min_vruntime)
      min_vruntime = temp_min;

    // Determine if object being operated on needs to change
    if (timeline.Size() > 0) {
      if (timeline.Get(timeline.Min())->ReturnVruntime() > min_vruntime) {
        // Delete and reinsert object
        temp_task = timeline.Get(timeline.Min());
        timeline.Remove(timeline.Min());
        timeline.Insert(temp_task->ReturnVruntime(), temp_task);
      }
    }

    // Check if any tasks can be done
    if (timeline.Size() != 0) {
      // Decrease root duration by 1 and increase min_vruntime by 1
      timeline.Get(timeline.Min())->DecreaseDuration();
      timeline.Get(timeline.Min())->IncreaseRuntime();

      // Check to see if task is finished
      if (timeline.Get(timeline.Min())->IsFinished()) {
        // Normal output but process's name has a star and is deleted
        std::cout << tick << " [" << tasks_running << "]: " <<
        timeline.Get(timeline.Min())->ReturnIdentifier() << "*" << std::endl;
        // Remove object from tasks and the timeline
	tasks_running--;
        counter--;
        for (i=0; i < tasks.size(); i++) {
          if (tasks[i]->IsFinished()) {
            delete tasks[i];
            tasks.erase(tasks.begin()+i);
            timeline.Remove(timeline.Min());
          }
        }
      } else {
        // Normal output
        std::cout << tick << " [" << tasks_running << "]: " <<
        timeline.Get(timeline.Min())->ReturnIdentifier() << std::endl;
      }
    } else {
      // No tasks are running
      std::cout << tick << " [0]: _" << std::endl;
    }

    // Increment ticks and if all tasks aren't done, run again
    tick++;
  }
  return 0;
}
