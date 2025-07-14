# JobQueue

# 🧵 Inter-Process Priority Job Queue System

This project implements a **priority job queue system** for managing jobs between processes using shared memory and semaphores. It provides multiple layers of abstraction, including low-level job structures, job queues, and synchronized access with IPC and semaphores.

---

## 📦 Project Structure

```bash
.
├── ipc_jobqueue.c      # IPC wrapper for shared memory-based job queues
├── job.c               # Job structure and utility functions
├── joblog.c            # Persistent job logging
├── pri_jobqueue.c      # Priority-based in-memory job queue
├── sem_jobqueue.c      # Semaphore-synchronized job queue (thread-safe)
