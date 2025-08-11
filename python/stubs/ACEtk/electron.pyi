"""
Electron ACE blocks
"""
from __future__ import annotations
import typing
__all__ = ['TransitionEnergyBlock']
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
