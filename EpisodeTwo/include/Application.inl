template<typename S, typename... A>
void Application::run(A&&...args)
{
   pushState<S>(std::forward<A>(args)...);
   m_running = true;
   GetLogger().logDebug("Running game...");
   gameLoop();
}

template<typename S, typename... A>
void Application::pushState(A&&... args)
{
   m_states.emplace(new S(*this, std::forward<A>(args)...));
}