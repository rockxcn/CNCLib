﻿using Proxxon.Repository.Entities;
using Proxxon.Repository.Mappings;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.ModelConfiguration.Conventions;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Proxxon.Repository.Context
{
    public class ProxxonContext : DbContext
    {
        public ProxxonContext()
        {
            Configure();
        }

        public ProxxonContext(string connectionString):base(connectionString)
        {
            Configure();    
        }

        public DbSet<Machine> Machines { get; set; }
		public DbSet<MachineCommand> MachineCommands { get; set; }
		public DbSet<Configuration> Configurations { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Configurations.Add(new MachineMapping());

			// Machine -------------------------------------

			modelBuilder.Entity<Machine>()
				.HasKey(m => m.MachineID);
			
			modelBuilder.Entity<Machine>().Property((m) => m.Name).
                IsRequired().
                HasMaxLength(64);

            modelBuilder.Entity<Machine>().Property((m) => m.ComPort).
                IsRequired().
                HasMaxLength(32);

			modelBuilder.Entity<Machine>().Property((m) => m.Axis).IsRequired();
			
			modelBuilder.Entity<Machine>().Property((m) => m.SizeX).IsRequired();
			modelBuilder.Entity<Machine>().Property((m) => m.SizeY).IsRequired();
			modelBuilder.Entity<Machine>().Property((m) => m.SizeZ).IsRequired();

			// MachineCommand -------------------------------------

			modelBuilder.Entity<MachineCommand>()
				.HasKey(mc => mc.MachineCommandID);

			modelBuilder.Entity<MachineCommand>().Property((m) => m.CommandString).
				IsRequired().
				HasMaxLength(64);
		
			// Configuration -------------------------------------

			modelBuilder.Entity<Configuration>()
				.HasKey(m => new { m.Group, m.Name });

			modelBuilder.Entity<Configuration>().Property((m) => m.Group).
				IsRequired().
				HasMaxLength(256);

			modelBuilder.Entity<Configuration>().Property((m) => m.Name).
				IsRequired().
				HasMaxLength(256);

			modelBuilder.Entity<Configuration>().Property((m) => m.Type).
				IsRequired().
				HasMaxLength(256);

			modelBuilder.Entity<Configuration>().Property((m) => m.Value).
				HasMaxLength(4000);

			// -------------------------------------
			
			modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
           
            base.OnModelCreating(modelBuilder);

        }

        private void Configure()
        {
            System.Data.Entity.Database.SetInitializer<ProxxonContext>(new ProxxonInitializer());
            Configuration.LazyLoadingEnabled = false;
            Configuration.ProxyCreationEnabled = false;
            Configuration.AutoDetectChangesEnabled = true;
            Configuration.ValidateOnSaveEnabled = true; 
        }
    }
}
