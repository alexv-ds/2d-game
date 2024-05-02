export module engine.window:components;

export namespace engine {

  namespace window {
    struct Opened {};
    struct Focused {};
  }// namespace window

  namespace window::phases {
    struct EventPollPre {};
    struct EventPoll {};
  }// namespace window::phases
}// namespace engine