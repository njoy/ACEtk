"""
Photonuclear ACE blocks and components
"""
from __future__ import annotations
import typing
__all__ = ['PrincipalCrossSectionBlock', 'SecondaryParticleLocatorBlock']
class PrincipalCrossSectionBlock:
    """
    The photoatomic ESZG block with the principal cross sections
    
    The PrincipalCrossSectionBlock class contains 3 or 4 arrays of the same
    length:
      - the energy points
      - the total cross section
      - the elastic scattering cross section (optional)
      - the heating numbers
    
    The size of each (the total number of energy points) is stored in NXS(3).
    """
    @typing.overload
    def __init__(self, energies: list[float], total: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energies    the energy values
            total       the total cross section values
            heating     the average heating cross section values
        """
    @typing.overload
    def __init__(self, energies: list[float], total: list[float], elastic: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energies    the energy values
            total       the total cross section values
            elastic     the elastic cross section values
            heating     the average heating cross section values
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
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def elastic(self) -> ...:
        """
        The elastic cross section values (this can be empty)
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
    def heating(self) -> ...:
        """
        The average heating numbers
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
    def total(self) -> ...:
        """
        The total cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleLocatorBlock:
    """
    The photonuclear IXSU block with the secondary particle information and locators
    
    The SecondaryParticleLocatorBlock class contains a particle type, a number
    of reactions and 10 locators for each secondary particle type.
    
    The number of available available particle types is stored in NXS(5).
    """
    def ANDH(self, index: int) -> int:
        """
        The locator to the ANDH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def DLWH(self, index: int) -> int:
        """
        The locator to the DLWH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def IP(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def LANDH(self, index: int) -> int:
        """
        The locator to the LANDH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def LDLWH(self, index: int) -> int:
        """
        The locator to the LDLWH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def LSIGH(self, index: int) -> int:
        """
        The locator to the LSIGH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def MTRH(self, index: int) -> int:
        """
        The locator to the MTRH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def NP(self, index: int) -> int:
        """
        The number of reactions for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def PHN(self, index: int) -> int:
        """
        The locator to the PHN block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def PXS(self, index: int) -> int:
        """
        The locator to the PXS block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def SIGH(self, index: int) -> int:
        """
        The locator to the SIGH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def TYRH(self, index: int) -> int:
        """
        The locator to the TYRH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def __init__(self, types: list[int], numbers: list[int], locators: list[list[int[10]]]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            types       the particle types
            numbers     the number of reactions for each particle type
            locators    the locators for each secondary particle type
        """
    def has_IP(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
            self    the block
            type    the particle type
        """
    def has_particle_type(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
            self    the block
            type    the particle type
        """
    def index(self, type: int) -> int:
        """
        Return the index (one-based) of the particle type
        
            self    the block
            type    the particle type
        """
    def number_secondary_particle_production_reactions(self, index: int) -> int:
        """
        The number of reactions for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def particle_type(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
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
    def NTYPE(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
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
    def number_additional_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
