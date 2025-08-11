"""
Electron ACE blocks
"""
from __future__ import annotations
import typing
__all__ = ['BremsstrahlungCorrectionFactorBlock', 'BremsstrahlungProductionBlock', 'MottScatteringCorrectionBlock', 'RadiationStoppingPowerBlock', 'RileyCrossSectionBlock', 'TransitionEnergyBlock']
class BremsstrahlungCorrectionFactorBlock:
    """
    The electron CRB block with the bremsstrahlung production correction factor data
    
    This block is part of the el format.
    
    The BremsstrahlungCorrectionFactorBlock class contains 2 arrays of the
    same length:
      - The energy points
      - The correction factor values
      
    The size NCRB of each (the total number of electron energy points) is
    stored in NXS(5).
    """
    def __init__(self, energies: list[float], corrections: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            energies       the energy values
            corrections    the correction factor values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NCRB(self) -> int:
        """
        The number of energy points
        """
    @property
    def corrections(self) -> ...:
        """
        The bremsstrahlung production correction factors
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class BremsstrahlungProductionBlock:
    """
    The electron XSB block with the bremsstrahlung photon production data
    
    This block is part of el03 format.
    
    The BremsstrahlungProductionBlock class contains a variable number of
    arrays of differing lengths:
      - The electron energy points
      - The photon energy ratio points
      - The cross section values
      
    The size NEB of the electron energy values array (the total number of
    electron energy points) is stored in NXS(5). The size NPB of the photon
    energy ratio values array (the total number of photon energy points) is
    stored in NXS(6). The size of the bremsstrahlung production cross
    section array (the number of values for interpolation) is NEB*NPB.
    
    The cross section values are stored internally in column-major order.
    """
    def __init__(self,
                 electron_energies: list[float],
                 photon_ratios: list[float],
                 cross_sections: list[list[float]]) -> None:
        """
        Initialize the block
        
        Arguments:
            electron_energies    the electron energy points
            photon_ratios        the photon energy ratio points
            cross_sections       the bremsstrahlung cross section values
        """
    def cross_section(self, ee_index: int, pr_index: int) -> float:
        """
        A single bremsstrahlung cross section value
        
        Arguments:
            ee_index    the electron energy index (one-based)
            pr_index    the photon energy ratio index (one-based)
        """
    def cross_sections(self, index: int) -> ...:
        """
        The cross section values for a given electron energy index
        
        Arguments:
            index   the electron energy index (one-based)
        """
    def electron_energy(self, index: int) -> float:
        """
        A single electron energy point
        
        Arguments:
            index   the electron energy index (one-based)
        """
    def photon_ratio(self, index: int) -> float:
        """
        A single photon energy ratio point
        
        Arguments:
            index   the photon energy ratio index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NEB(self) -> int:
        """
        The number of electron energy points
        """
    @property
    def NPB(self) -> int:
        """
        The number of photon energy ratio points
        """
    @property
    def cross_section_data(self) -> ...:
        """
        The bremsstrahlung cross section data array
        """
    @property
    def electron_energies(self) -> ...:
        """
        The electron energy points
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_cross_sections(self) -> int:
        """
        The number of cross section values
        """
    @property
    def number_electron_energies(self) -> int:
        """
        The number of electron energy points
        """
    @property
    def number_photon_ratios(self) -> int:
        """
        The number of photon energy ratio points
        """
    @property
    def photon_ratios(self) -> ...:
        """
        The photon energy ratio points
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class MottScatteringCorrectionBlock:
    """
    The electron MOT block with the Mott scattering correction data
    
    This block is part of el and el03 formats.
    
    The MottScatteringCorrectionBlock class contains 6 arrays of the same
    length:
      - The energy points
      - The Mott scattering correction h(theta) for theta = 0
      - The Mott scattering correction h(theta) for theta = pi/4
      - The Mott scattering correction h(theta) for theta = pi/2
      - The Mott scattering correction h(theta) for theta = 3*pi/4
      - The Mott scattering correction h(theta) for theta = pi
      
    The size NMOT of each (the total number of Mott scattering cross
    section energy points) is stored in NXS(4).
    """
    def __init__(self,
                 energies: list[float],
                 corrections0deg: list[float],
                 corrections45deg: list[float],
                 corrections90deg: list[float],
                 corrections135deg: list[float],
                 corrections180deg: list[float]) -> None:
        """
        Initialize the block
        
        Arguments:
            energies             the energy values
            corrections0deg      the Mott scattering corrections at 0 degrees
            corrections45deg     the Mott scattering corrections at 45 degrees
            corrections90deg     the Mott scattering corrections at 90 degrees
            corrections135deg    the Mott scattering corrections at 135 degrees
            corrections180deg    the Mott scattering corrections at 180 degrees
        """
    def mott_scattering_correction(self, index: int) -> ...:
        """
        The Mott scattering correction for an index.
        
        Arguments:
            index   the index (1 to 5 inclusively, one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NMOT(self) -> int:
        """
        The number of energy points
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy points
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class RadiationStoppingPowerBlock:
    """
    The electron RAD block with the radiation stopping power data
    
    This block is part of el and el03 formats.
    
    The RadiationStoppingPowerBlock class contains 3 arrays of the same
    length:
      - The energy points
      - The normalized stopping powers
      - The electron-electron bremsstrahlung correction (NEL == 3)
    
    The size NRAD of each (the total number of electron energy points) is
    stored in NXS(3).
    """
    def __init__(self,
                 energies: list[float],
                 stopping_powers: list[float],
                 energies: list[float] = None) -> None:
        """
        Initialize the block
        
        Arguments:
            self               the block
            energies           the energy values
            stopping_powers    the normalized radiative stopping power values
            corrections        the electron-electron bremsstrahlung correction values (NEL == 3)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NRAD(self) -> int:
        """
        The number of energy points
        """
    @property
    def corrections(self) -> ...:
        """
        The electron-electron bremsstrahlung correction factors (NEL == 3)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy points for radiation stopping power interpolation
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def stopping_powers(self) -> ...:
        """
        The normalized radiation stopping powers
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class RileyCrossSectionBlock:
    """
    The electron RLY block with the Riley cross section data
    
    This block is part of el and el03 formats.
    
    The RileyCrossSectionBlock class contains 9 arrays of the same length.
    Each array contains an energy value from 1 to 256 keV followed by the
    set of Riley scattering cross section parameters at that energy.
    
    The size of each Riley set array is 14 (1 energy + 13 parameters).
    This size value is hard-coded and is not stored in the NXS array.
    """
    def __init__(self,
                 rileySet256keV: list[float],
                 rileySet128keV: list[float],
                 rileySet64keV: list[float],
                 rileySet32keV: list[float],
                 rileySet16keV: list[float],
                 rileySet8keV: list[float],
                 rileySet4keV: list[float],
                 rileySet2keV: list[float],
                 rileySet1keV: list[float]) -> None:
        """
        Initialize the block
        
        Arguments:
            rileySet256keV    the Riley cross section parameters at 256 keV
            rileySet128keV    the Riley cross section parameters at 128 keV
            rileySet64keV     the Riley cross section parameters at 64 keV
            rileySet32keV     the Riley cross section parameters at 32 keV
            rileySet16keV     the Riley cross section parameters at 16 keV
            rileySet8keV      the Riley cross section parameters at 8 keV
            rileySet4keV      the Riley cross section parameters at 4 keV
            rileySet2keV      the Riley cross section parameters at 2 keV
            rileySet1keV      the Riley cross section parameters at 1 keV
        """
    def energy(self, index: int) -> float:
        """
        The energy of a Riley cross section parameter set
        
        Arguments:
            index   the index (1 to 9 inclusively, one-based)
        """
    def parameter_set(self, index: int) -> ...:
        """
        The Riley cross section parameter set at the index
        
        Arguments:
            index   the index (1 to 9 inclusively, one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NRLY(self) -> :
        """
        The number of Riley cross section parameter sets
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> :
        """
        The number of Riley cross section parameter sets
        """
    @property
    def parameter_set_length(self) -> :
        """
        The length of a Riley cross section parameter set
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TransitionEnergyBlock:
    """
    The electron EKT block with the transition energy data
    
    This block is part of el and el03 formats.
    
    The TransitionEnergyBlock class contains 2 or 4 data points:
      - The K edge energy below which no electron induced relaxation will
        occur (EDG)
      - The K x-ray or Auger electron emission energy (EEK)
      - The (2) bremsstrahlung extrapolation transition points (NEL != 3)
    """
    def __init__(self, values: list[float]) -> None:
        """
        Initialize the block
        
        Arguments:
            self      the block
            values    the transition energy values (4 for el, 2 for el03)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def EDG(self) -> float:
        """
        The K edge energy
        """
    @property
    def EEK(self) -> float:
        """
        The K x-ray or Auger electron emission energy
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def k_edge_energy(self) -> float:
        """
        The K edge energy
        """
    @property
    def k_xray_emission_energy(self) -> float:
        """
        The K x-ray or Auger electron emission energy
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def lower_bremsstrahlung_transition_energy(self) -> float:
        """
        The lower bremsstrahlung extrapolation transition energy
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def upper_bremsstrahlung_transition_energy(self) -> float:
        """
        The upper bremsstrahlung extrapolation transition energy
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
