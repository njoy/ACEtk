"""
Multigroup MC ACE blocks and components
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AbsorptionCrossSectionBlock', 'FissionChiDataBlock', 'FissionCrossSectionBlock', 'IncidentParticleGroupStructureBlock', 'MomentumTransferBlock', 'StoppingPowerBlock', 'TotalCrossSectionBlock']
class AbsorptionCrossSectionBlock:
    """
    The multigroup absorption cross section block
    
    The AbsorptionCrossSectionBlock class contains 1 array: 
      - absorption cross section for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        absorption_cross_section : list of float 
             the absorption cross section for each group
    
    """
    def __init__(self, absorption_cross_section: list[float]) -> None:
        """
        Create the ABS block with the absorption cross section values 
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
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def SIGABS(self) -> ...:
        """
        The absorption cross section values
        """
    @property
    def absorption_cross_section(self) -> ...:
        """
        The absorption cross section values
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FissionChiDataBlock:
    """
    The multigroup fission fraction (PFNS) section block
    
    The FissionChiDataBlock class contains 1 array: 
      - the fission fraction (PFNS) for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        fission_fraction : list of float 
             the fission fraction (PFNS) for each group
    
    """
    def __init__(self, fission_fraction: list[float]) -> None:
        """
        Create the CHI block with the fission fraction values 
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
    def FISFR(self) -> ...:
        """
        The fission fraction (PFNS) values
        """
    @property
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def fission_fraction(self) -> ...:
        """
        The fission fraction (PFNS) values
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FissionCrossSectionBlock:
    """
    The multigroup fission cross section block
    
    The FissionCrossSectionBlock class contains 1 array: 
      - fission cross section for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        fission_cross_section : list of float 
             the fission cross section for each group
    
    """
    def __init__(self, fission_cross_section: list[float]) -> None:
        """
        Create the FISS block with the fission cross section values 
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
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def SIGFISS(self) -> ...:
        """
        The fission cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def fission_cross_section(self) -> ...:
        """
        The fission cross section values
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class IncidentParticleGroupStructureBlock:
    """
    The multigroup group structure block
    
    The IncidentParticleGroupStructureBlock class contains 2 arrays of the same length:
      - the mean energies of each group (in MeV)
      - the widths of each group (in MeV)
    The size of each (the total number of energy groups) is stored in NXS(5).
    
    Parameters
    ----------
        group_means : list of floats 
            the mean energies of each group in MeV 
        group_widths : list of floats 
            the widths of each group in MeV 
    
    """
    def __init__(self, group_means: list[float], group_widths: list[float]) -> None:
        """
        Create the ERG block with group means and widths 
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
    def ECENT(self) -> ...:
        """
        The mean energies of each group in MeV
        """
    @property
    def EWID(self) -> ...:
        """
        The widths of each group MeV
        """
    @property
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def group_means(self) -> ...:
        """
        The mean energies of each group in MeV
        """
    @property
    def group_widths(self) -> ...:
        """
        The widths of each group MeV
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class MomentumTransferBlock:
    """
    The multigroup momentum transfer block
    
    The MomentumTransferBlock class contains 1 array: 
      - the momentum transfer values for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        momentum_transfer : list of float 
             the momentum transfer values for each group
    
    """
    def __init__(self, momentum_transfer: list[float]) -> None:
        """
        Create the MOM block with the momentum transfer values 
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
    def MOMTR(self) -> ...:
        """
        The momentum transfer values
        """
    @property
    def NGRP(self) -> int:
        """
        The number of energy groups
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
    def momentum_transfer(self) -> ...:
        """
        The momentum transfer values
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class StoppingPowerBlock:
    """
    The multigroup stopping power section block
    
    The StoppingPowerBlock class contains 1 array: 
      - the stopping power for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        stopping_power : list of float 
             the stopping power for each group
    
    """
    def __init__(self, stopping_power: list[float]) -> None:
        """
        Create the STOP block with the stopping power values 
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
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def SPOW(self) -> ...:
        """
        The stopping power values
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def stopping_power(self) -> ...:
        """
        The stopping power values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TotalCrossSectionBlock:
    """
    The multigroup total cross section block
    
    The TotalCrossSectionBlock class contains 1 array: 
      - total cross section for each group 
    The size the array (the total number of energy groups) is stored in NXS(5). 
    
    Parameters
    ----------
        total_cross_section : list of float 
             the total cross section for each group
    
    """
    def __init__(self, total_cross_section: list[float]) -> None:
        """
        Create the TOT block with the total cross section values 
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
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def SIGTOT(self) -> ...:
        """
        The total cross section values
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
    def number_energy_groups(self) -> int:
        """
        The number of energy groups
        """
    @property
    def total_cross_section(self) -> ...:
        """
        The total cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
