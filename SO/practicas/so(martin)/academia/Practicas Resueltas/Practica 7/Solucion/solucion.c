/* Implementaci?n de sem?foros contadores utilizando sem?foros binarios.
*/

wait (sem_t *s)
{
  waitB(mutex);
  s--;
  if (s<0)
    {
      signalB(mutex);
      waitB(delay);
    }
  signalB(mutex);
}

signal (sem_t *s)
{
  waitB(mutex);
  s++;
  if (s <= 0)
    signalB(delay);  
  else
    signalB(mutex);
}
