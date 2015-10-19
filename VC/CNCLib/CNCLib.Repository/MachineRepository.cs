﻿using CNCLib.Repository.Context;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CNCLib.Repository;
using Framework.Tools;
using System.Data.Entity;
using Framework.EF;

namespace CNCLib.Repository
{
    public class MachineRepository
    {
		public Entities.Machine[] GetMachines()
		{
			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				return uow.Query<Entities.Machine>().
					ToList().ToArray();
			}
		}

		public Entities.Machine GetMachine(int id)
        {
			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				return uow.Query<Entities.Machine>().
					Where((m) => m.MachineID == id).
					Include((d) => d.MachineCommands).
					Include((d) => d.MachineInitCommands).
					FirstOrDefault();
			}
        }

		public void Delete(Entities.Machine m)
        {
			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				try
				{
					uow.BeginTransaction();

					m.MachineCommands = null;
					m.MachineInitCommands = null;
					uow.MarkDeleted(m);
					uow.ExecuteSqlCommand("delete from MachineCommand where MachineID = " + m.MachineID);
					uow.ExecuteSqlCommand("delete from MachineInitCommand where MachineID = " + m.MachineID);
					uow.Save();

					uow.CommitTransaction();
				}
				catch (Exception)
				{
					uow.RollbackTransaction();
					throw;
				}
			}
        }

		public Entities.MachineCommand[] GetMachineCommands(int machineID)
		{
			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				return uow.Query<CNCLib.Repository.Entities.MachineCommand>().
					Where(c => c.MachineID == machineID).
					ToList().ToArray();
			}
		}

		public Entities.MachineInitCommand[] GetMachineInitCommands(int machineID)
		{
			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				return uow.Query<CNCLib.Repository.Entities.MachineInitCommand>().
					Where(c => c.MachineID == machineID).
					ToList().ToArray();
			}
		}

		public int StoreMachine(Entities.Machine machine)
		{
			// search und update machine

			using (IUnitOfWork uow = UnitOfWorkFactory.Create())
			{
				int id = machine.MachineID;

				try
				{
					uow.BeginTransaction();

					var machineInDb = uow.Query<Entities.Machine>().
						Where((m) => m.MachineID == id).
						Include((d) => d.MachineCommands).
						Include((d) => d.MachineInitCommands).
						FirstOrDefault();
					var machineCommands = machine.MachineCommands ?? new List<Entities.MachineCommand>();
					var machineInitCommands = machine.MachineInitCommands ?? new List<Entities.MachineInitCommand>();

					if (machineInDb == default(Entities.Machine))
					{
						// add new

						machineInDb = machine;
						uow.MarkNew(machineInDb);
						uow.Save();						// this will save the Commands as well
						id = machineInDb.MachineID;
					}
					else
					{
						// syn with existing

						machineInDb.CopyValueTypeProperties(machine);

						// search und update machinecommands (add and delete)

						EFTools.Sync<Entities.MachineCommand>(uow, 
							machineInDb.MachineCommands, 
							machineCommands, 
							(x, y) => x.MachineCommandID > 0 && x.MachineCommandID == y.MachineCommandID);

						EFTools.Sync<Entities.MachineInitCommand>(uow,
							machineInDb.MachineInitCommands,
							machineInitCommands,
							(x, y) => x.MachineInitCommandID > 0 && x.MachineInitCommandID == y.MachineInitCommandID);

						uow.Save();
					}

					uow.CommitTransaction();
				}
				catch (Exception ex)
				{
					uow.RollbackTransaction();
					throw;
				}

				return id;
			}
		}
    }
}