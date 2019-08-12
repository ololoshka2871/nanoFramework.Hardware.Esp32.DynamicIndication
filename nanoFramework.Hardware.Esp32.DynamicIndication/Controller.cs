using System;
using System.Runtime.CompilerServices;

namespace nanoFramework.Hardware.Esp32.DynamicIndication
{
	public class Controller : IDisposable
	{
		#region Fields

		public static readonly uint DefaultUpdatePeriod_us = 5000;

		#endregion Fields

		#region Constructors

		public Controller(int[] dataPins, int[] selectorPins, int dataBitsPreIndicator)
		{
			var indicators_count = dataPins.Length / dataBitsPreIndicator * selectorPins.Length;
			if (dataPins.Length % dataBitsPreIndicator != 0)
			{
				throw new ArgumentException("Data pins count mast be multiply of dataBitsPreIndicator");
			}
			NativeInit(dataPins, selectorPins, indicators_count);
			UpdatePeriod_us = DefaultUpdatePeriod_us;
		}

		#endregion Constructors

		#region Destructors

		~Controller()
		{
			Dispose(false);
		}

		#endregion Destructors

		#region Methods

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		protected virtual void Dispose(bool disposing)
		{
			NativeDispose();
		}

		#endregion Methods

		#region Properties

		/// <summary>
		/// Is indication running?
		/// </summary>
		public bool Enabled
		{
			get => NativeIsEnabled();
			set => NativeSetEnabled(value);
		}

		/// <summary>
		/// Opdate period in mucroseconds
		/// </summary>
		public uint UpdatePeriod_us
		{
			get => NativeGetUpdateInterval();
			set => NativeSetUpdateInterval(value);
		}

		/// <summary>
		/// indicator data.
		///
		/// Each element for one indicator, even if most significant bits are not used
		/// </summary>
		public void SetData(uint[] data) => NativeSetData(data);

		#endregion Properties

		#region Stubs

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeDispose();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern uint NativeGetUpdateInterval();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeInit(int[] dataPins, int[] selectorPins, int dataBitsPreIndicator);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern bool NativeIsEnabled();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeSetData(uint[] data);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeSetEnabled(bool enabled);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeSetUpdateInterval(uint updateInterval_us);

		#endregion Stubs
	}
}