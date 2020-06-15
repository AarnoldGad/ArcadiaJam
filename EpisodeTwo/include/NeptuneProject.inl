template<typename S, typename... A>
void NeptuneProject::run(A&&... args)
{
   pushState<S>(std::forward<A>(args)...);
   m_running = true;
   GetLogger().logDebug("Running game...");
   gameLoop();
}

template<typename S, typename... A>
void NeptuneProject::pushState(A&&... args)
{
   m_states.emplace(new S(*this, std::forward<A>(args)...));
}