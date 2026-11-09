#include <exception>
#include <string>

class FleetOperationError : public std::exception {
 protected:
  std::string message;

 public:
  explicit FleetOperationError(const std::string& msg) : message(msg) {}

  const char* what() const noexcept override { return message.c_str(); }
};

class FocusError : public FleetOperationError {
 public:
  explicit FocusError(const std::string& more_info = "")
      : FleetOperationError("Error during trying to focus. " + more_info) {}
};

class InspectionError : public std::exception {
 protected:
  std::string message;

 public:
  explicit InspectionError(const std::string& msg) : message(msg) {}

  const char* what() const noexcept override { return message.c_str(); }
};