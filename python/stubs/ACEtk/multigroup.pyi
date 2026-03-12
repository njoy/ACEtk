"""
Multigroup MC ACE blocks and components
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AbsorptionCrossSectionBlock', 'EditCrossSectionBlock', 'EditReactionNumberBlock', 'FissionChiDataBlock', 'FissionCrossSectionBlock', 'IncidentParticleGroupStructureBlock', 'MomentumTransferBlock', 'SecondaryParticleTypeBlock', 'StoppingPowerBlock', 'TotalCrossSectionBlock']
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
class EditCrossSectionBlock:
    """
    The EditCrossSectionBlock class contains the edit cross section values 
    in the XSED block. The number of edit reactions is in NXS(4) and the 
    number of groups is NXS(5). The order of the edit cross sections is the 
    same as the order of the edit reaction numbers in the MTED block. 
    
    Parameters
    ----------
        reactions : list of lists of float 
            The edit reaction cross section data 
    
    """
    def XS(self, index: int) -> ...:
        """
        Return the cross section at a specific index
        
        Parameters
        ----------
            index : int 
                The edit reaction index 
        
        Returns
        -------
            list of floats 
                The cross section values for the edit reaction 
        
        Raises
        ------
            Exception 
                When the index is out of range 
        """
    def __init__(self, reactions: list[list[float]]) -> None:
        """
        Create the XSED block with the edit cross section values 
        """
    def edit_cross_section(self, index: int) -> ...:
        """
        Return the cross section at a specific index
        
        Parameters
        ----------
            index : int 
                The edit reaction index 
        
        Returns
        -------
            list of floats 
                The cross section values for the edit reaction 
        
        Raises
        ------
            Exception 
                When the index is out of range 
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
    def NEDIT(self) -> int:
        """
        The number of edit reactions
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
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_edit_reactions(self) -> int:
        """
        The number of edit reactions
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
class EditReactionNumberBlock:
    """
    The multigroup MTED block with the edit reaction MT numbers
    
    The EditReactionNumberBlock class contains the edit reaction MT numbers
    
    The number of edit reactions is stored in NXS(4).
    
    Parameters
    ----------
        edit_reaction_numbers : list of int 
             the edit reaction MT numbers
    
    """
    def MT(self, index: int) -> int:
        """
        The edit reaction number for an index
        
        Parameters
        ----------
            index : int   
                the index (one-based)
        
        Returns
        -------
            int 
                The edit reaction number at the index given
        
        Raises
        ------
            Exception 
                If the index provided doesn't exist in the block 
        """
    def __init__(self, edit_reaction_numbers: list[int]) -> None:
        """
        Create the MTED block with the edit reaction MT numbers
        """
    def edit_reaction_number(self, index: int) -> int:
        """
        The edit reaction number for an index
        
        Parameters
        ----------
            index : int   
                the index (one-based)
        
        Returns
        -------
            int 
                The edit reaction number at the index given
        
        Raises
        ------
            Exception 
                If the index provided doesn't exist in the block 
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not a reaction MT is present in the edit reactions
        
        Parameters
        ----------
            mt : int   
                the mt number
        
        Returns
        -------
            bool 
                True if the MT exists in the edit reactions
        """
    def has_edit_reaction_number(self, reaction: int) -> bool:
        """
        Return whether or not a reaction MT is present in the edit reactions
        
        Parameters
        ----------
            mt : int   
                the mt number
        
        Returns
        -------
            bool 
                True if the MT exists in the edit reactions
        """
    def index(self, mt: int) -> int:
        """
        Return the index (one-based) of the edit reaction number, if present
        
        Parameters
        ----------
            mt : int   
                the mt number
        
        Returns
        -------
            int 
                The index of the MT number
        
        Raises
        ------
            Exception 
                If the MT provided doesn't exist in the block 
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
    def MTs(self) -> ...:
        """
        The edit reaction numbers
        """
    @property
    def NEDIT(self) -> int:
        """
        The number of edit reactions 
        """
    @property
    def edit_reaction_numbers(self) -> ...:
        """
        The edit reaction numbers
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
    def number_edit_reactions(self) -> int:
        """
        The number of edit reactions
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
class SecondaryParticleTypeBlock:
    """
    The multigroup IPT block with the secondary particle types
    
    The SecondaryParticleTypeBlock class contains the secondary particle types
    for which data is available. The allowed particle types are: 
        1  -  neutron 
        2  -  photon 
    The number of available particle types is stored in NXS(8).
    
    Parameters
    ----------
        types : list of int 
            the secondary particle types
    
    """
    def IPT(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The particle type 
        
        Raises
        ------
            Exception 
                When the index is out of range 
        """
    def __init__(self, types: list[int]) -> None:
        """
        Create the IPT block
        """
    def has_IPT(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
        Parameters
        ----------
            type : int 
                the particle type
        
        Returns
        -------
            bool 
                Whether or not the particle type is present 
        """
    def has_particle_type(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
        Parameters
        ----------
            type : int 
                the particle type
        
        Returns
        -------
            bool 
                Whether or not the particle type is present 
        """
    def index(self, type: int) -> int:
        """
        Return the index (one-based) of the particle type
        
        Parameters
        ----------
            type : int 
                The particle type 
        
        Returns
        -------
            int 
                The index of the particle type (one-based) 
        
        Raises
        ------
            Exception 
                When the particle type is not present 
        """
    def particle_type(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The particle type 
        
        Raises
        ------
            Exception 
                When the index is out of range 
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
    def IPTs(self) -> ...:
        """
        The particle types
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types
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
    def number_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types
        """
    @property
    def particle_types(self) -> ...:
        """
        The particle types
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
