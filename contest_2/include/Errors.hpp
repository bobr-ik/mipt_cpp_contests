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

class InvalidArgument : public FleetOperationError {
 public:
  explicit InvalidArgument(const std::string& more_info = "")
      : FleetOperationError("Invalid argument. " + more_info) {}
};

class InvalidOperation : public FleetOperationError {
 public:
  explicit InvalidOperation(const std::string& more_info = "")
      : FleetOperationError("Invalid operator. " + more_info) {}

};

class InspectionError : public FleetOperationError {
 public:
  explicit InspectionError(const std::string& more_info = "")
      : FleetOperationError("Inspection error. " + more_info) {}
};

class RemoveError : public FleetOperationError {
 public:
  explicit RemoveError(const std::string& more_info = "")
      : FleetOperationError("Remove error. " + more_info) {}
};

class Quit : std::exception {
  protected:
  std::string message;

 public:
  explicit Quit(const std::string& msg) : message(msg) {}

  const char* what() const noexcept override { return message.c_str(); }
};