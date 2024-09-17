"""
Dosimetry ACE blocks and components
"""
import ACEtk.ACEtk.continuous
from __future__ import annotations
import typing
__all__ = ['CrossSectionBlock', 'CrossSectionData']
class CrossSectionBlock:
    """
    The continuous energy LSIG and SIGD block with the dosimetry cross section data
    
    The CrossSectionBlock class contains NXS(4) sets of cross section data,
    one for each reaction number on the MTR block. The order of these cross
    section data sets is the same as the order of the reaction numbers in the
    MTR block.
    """
    def LSIG(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, xs: list[CrossSectionData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            xs      the cross section data
        """
    def cross_section_data(self, index: int) -> CrossSectionData:
        """
        Return the cross section data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def cross_section_locator(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
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
    def NTR(self) -> int:
        """
        The number of available reactions
        """
    @property
    def data(self) -> list[CrossSectionData]:
        """
        The cross section data
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
    def number_reactions(self) -> int:
        """
        The number of available reactions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class CrossSectionData:
    """
    Cross section data from the SIGD block for a single reaction
    
    The CrossSectionData class contains the interpolation regions (if any are
    defined) along with the energy and cross section values. The dosimetry cross
    sections are different from the other cross section data blocks in that the
    data is not given on a common energy grid.
    """
    @typing.overload
    def __init__(self, energies: list[float], xs: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self        the block
            energies    the energy values
            xs          the xs values
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], xs: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            xs              the xs values
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
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
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
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> ACEtk.ACEtk.continuous.InterpolationData:
        """
        The interpolation data
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
        The number of energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
