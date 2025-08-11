"""
Electron ACE blocks
"""
from __future__ import annotations
import typing
__all__ = ['TransitionEnergyBlock']
class RadiationStoppingPowerBlock:
    """The electron RAD block with the radiation stopping power data
    
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
        """Initialize the block
        
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
class TransitionEnergyBlock:
    """The electron EKT block with the transition energy data
    
    This block is part of el and el03 formats.
    
    The TransitionEnergyBlock class contains 2 or 4 data points:
      - The K edge energy below which no electron induced relaxation will
        occur (EDG)
      - The K x-ray or Auger electron emission energy (EEK)
      - The (2) bremsstrahlung extrapolation transition points (NEL != 3)
    """
    def __init__(self, values: list[float]) -> None:
        """Initialize the block
        
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
