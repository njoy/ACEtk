"""
Multigroup MC ACE blocks and components
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AbsorptionCrossSectionBlock', 'BandP0Data', 'BandXPNData', 'EditCrossSectionBlock', 'EditReactionNumberBlock', 'FissionChiDataBlock', 'FissionCrossSectionBlock', 'IncidentParticleGroupStructureBlock', 'MomentumTransferBlock', 'NumberSecondaryAngularVariablesBlock', 'P0LocatorBlock', 'PNLocatorBlock', 'RectangularP0Data', 'RectangularXPNData', 'SecondaryAngularDistributionTypeBlock', 'SecondaryParticleGroupStructureBlock', 'SecondaryParticleGroupStructureLocatorBlock', 'SecondaryParticleTypeBlock', 'StoppingPowerBlock', 'TotalCrossSectionBlock', 'XPNLocatorBlock']
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
class BandP0Data:
    """
    P0 Block for the incident particle
    
    The BandP0Data class contains the P0 block for the outgoing
    particle when it is the same as the incident particle. It is 
    stored as a Square Band Matrix. Down-scatter groups are the
    super-diagonals in the matrix and up-scatter groups are the
    sub-diagonals in the matrix because the energy groups are
    sorted in descending order.
    
    Parameters
    ----------
        matrix : array-like 
            the two-dimensional matrix data values 
        down : int 
            the number of down-scatter groups 
        up : int 
            the number of up-scatter groups 
    
    Notes
    -----
    Any non-zero values in the matrix outside of the defined 
    bands will be lost in the construction of the BandP0Data  
    object. 
    
    """
    def __init__(self, matrix: list[list[float]], down: int, up: int) -> None:
        """
        Create the block
        """
    def group_down_scatter_groups(self, group: int) -> int:
        """
        The number of down-scatter groups for a specific incident group
        
        Parameters
        ----------
            group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            int 
                The number of down-scatter groups for the incident group 
        """
    def group_up_scatter_groups(self, group: int) -> int:
        """
        The number of up-scatter groups for a specific incident group
        
        Parameters
        ----------
            group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            int 
                The number of up-scatter groups for the incident group 
        """
    def incident_row(self, incident_group: int) -> list[float]:
        """
        The row of the matrix for a specific incident group
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            list of doubles 
                The matrix for for the incident group 
        """
    def p0_value(self, incident_group: int, outgoing_group: int) -> float:
        """
        The P0 matrix value for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The P0 value for the groups 
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
    def NDS(self) -> int:
        """
        The number of down-scatter groups
        """
    @property
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def NUS(self) -> int:
        """
        The number of up-scatter groups
        """
    @property
    def block_length(self) -> int:
        """
        The length of the XSS block
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
    def number_down_scatter_groups(self) -> int:
        """
        The number of down-scatter groups
        """
    @property
    def number_energy_groups(self) -> int:
        """
        The number energy groups
        """
    @property
    def number_up_scatter_groups(self) -> int:
        """
        The number of up-scatter groups
        """
    @property
    def p0_matrix(self) -> ...:
        """
        The P0 Matrix
        """
    @property
    def p0_matrix_list(self) -> ...:
        """
        The P0 matrix as a 1-D array
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class BandXPNData:
    """
    XPN Block for the incident particle
    
    The BandXPNData class contains the XPN block for the outgoing
    particle when it is the same as the incident particle. It is 
    stored as a Square Band Matrix. Down-scatter groups are the
    super-diagonals in the matrix and up-scatter groups are the
    sub-diagonals in the matrix because the energy groups are
    sorted in descending order.  The values are relative locators 
    in the PN matrix.
    
    Parameters
    ----------
        matrix : array-like of ints 
            the two-dimensional locator matrix data values 
        down : int 
            the number of down-scatter groups 
        up : int 
            the number of up-scatter groups 
    
    Notes
    -----
    Any non-zero values in the matrix outside of the defined 
    bands will be lost in the construction of the BandXPNData  
    object. 
    
    """
    def LPND(self, incident_group: int, outgoing_group: int) -> float:
        """
        The locator for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The XPN value for the groups 
        """
    def __init__(self, matrix: list[list[int]], down: int, up: int) -> None:
        """
        Create the block
        """
    def group_down_scatter_groups(self, group: int) -> int:
        """
        The number of down-scatter groups for a specific incident group
        
        Parameters
        ----------
            group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            int 
                The number of down-scatter groups for the incident group 
        """
    def group_up_scatter_groups(self, group: int) -> int:
        """
        The number of up-scatter groups for a specific incident group
        
        Parameters
        ----------
            group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            int 
                The number of up-scatter groups for the incident group 
        """
    def incident_row(self, incident_group: int) -> list[float]:
        """
        The row of the matrix for a specific incident group
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            list of int 
                The matrix for for the incident group 
        """
    def locator(self, incident_group: int, outgoing_group: int) -> float:
        """
        The locator for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The XPN value for the groups 
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
    def NDS(self) -> int:
        """
        The number of down-scatter groups
        """
    @property
    def NGRP(self) -> int:
        """
        The number of energy groups
        """
    @property
    def NUS(self) -> int:
        """
        The number of up-scatter groups
        """
    @property
    def block_length(self) -> int:
        """
        The length of the XSS block
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
    def number_down_scatter_groups(self) -> int:
        """
        The number of down-scatter groups
        """
    @property
    def number_energy_groups(self) -> int:
        """
        The number energy groups
        """
    @property
    def number_up_scatter_groups(self) -> int:
        """
        The number of up-scatter groups
        """
    @property
    def xpn_matrix(self) -> ...:
        """
        The XPN Matrix
        """
    @property
    def xpn_matrix_list(self) -> ...:
        """
        The XPN matrix as a 1-D array
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
class NumberSecondaryAngularVariablesBlock:
    """
    The multigroup NLEG2 block with the number of angular distribution variables
    
    The number of secondary particle numbers (NSEC) is stored in NXS(8).
    
    Parameters
    ----------
        numbers : list of int 
            the number of variables for each particle 
    
    """
    def NLEG2(self, index: int) -> int:
        """
        The number of angular distribution variables for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The number of angular distribution variables 
        
        Raises
        ------
            Exception 
                When the index is out of range 
        """
    def __init__(self, numbers: list[int]) -> None:
        """
        Create the NLEG2 block
        """
    def number_angular_distribution_variables(self, index: int) -> int:
        """
        The number of angular distribution variables for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The number of angular distribution variables 
        
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
    def NLEG2s(self) -> ...:
        """
        The list of number of angular distribution variables
        """
    @property
    def NSEC(self) -> int:
        """
        The number of secondary particles
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
    def number_angular_distribution_variables_list(self) -> ...:
        """
        The list of number of angular distribution variables
        """
    @property
    def number_secondary_particles(self) -> int:
        """
        The number of secondary particles
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class P0LocatorBlock:
    """
    The multigroup P0L block with locators for P0 blocks
    for the incident and secondary particle(s)
    
    The P0LocatorBlock class contains NSEC+1 locators, one for the incident particle
    and one for each secondary particle type given in the :class:`SecondaryParticleTypeBlock`. 
    The first locator is for the incident particle and the remaining are for the secondary 
    particles, in the same order as they are in the :class:`SecondaryParticleTypeBlock`.
    
    The number of secondary particle types, NSEC, is stored in NXS(8).
    
    Parameters
    ----------
        locators : list of int 
            the locators for each P0 block
    
    """
    def P01(self) -> int:
        """
        Return the locator for the P0 block for the incident particle  
        
        Returns
        -------
            int 
                The locator
        """
    def P02(self, particle: int) -> int:
        """
        Return the locator for the P0 block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
        """
    def __init__(self, locators: list[int]) -> None:
        """
        Create the block
        """
    def incident_locator(self) -> int:
        """
        Return the locator for the P0 block for the incident particle  
        
        Returns
        -------
            int 
                The locator
        """
    def secondary_locator(self, particle: int) -> int:
        """
        Return the locator for the P0 block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
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
    def NSEC(self) -> int:
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
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PNLocatorBlock:
    """
    The multigroup PNL block with locators for the PN blocks 
    for the incident and secondary particles
    
    The PNLocatorBlock class contains NSEC+1 locators, one for the incident particle
    and one for each secondary particle type given in the :class:`SecondaryParticleTypeBlock`. 
    The first locator is for the incident particle and the remaining are for the secondary 
    particles, in the same order as they are in the :class:`SecondaryParticleTypeBlock`. The 
    locators point to the PN blocks, which contain relative locators within the PN blocks.
    
    The number of secondary particle types, NSEC, is stored in NXS(8).
    
    Parameters
    ----------
        locators : list of int 
            the locators for each PN block
    
    """
    def LPN(self, particle: int) -> int:
        """
        Return the locator for the PN block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
        """
    def __init__(self, locators: list[int]) -> None:
        """
        Create the block
        """
    def is_isotropic(self, particle: int) -> bool:
        """
        Whether or not the secondary particle angular distribution is isotropic  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            bool 
                If the angular distribution is isotropic
        """
    def secondary_locator(self, particle: int) -> int:
        """
        Return the locator for the PN block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
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
    def LPN1(self) -> int:
        """
        The locator for the PN block for the incident particle  
        
        Returns
        -------
            int 
                The locator
        """
    @property
    def NSEC(self) -> int:
        """
        The number of secondary particle types
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_isotropic(self) -> bool:
        """
        Whether or not the incident particle outgoing angular distribution is isotropic  
        
        Returns
        -------
            bool 
                If the angular distribution is isotropic
        """
    @property
    def incident_locator(self) -> int:
        """
        The locator for the PN block for the incident particle  
        
        Returns
        -------
            int 
                The locator
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
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class RectangularP0Data:
    """
    P0 Block for outgoing particles that are not the incident particle
    
    The RectangularP0Data class contains the P0 block for the outgoing
    particle when it is not the incident particle. 
    
    Parameters
    ----------
        matrix : array-like 
            the two-dimensional matrix data values 
    
    """
    def __init__(self, matrix: list[list[float]]) -> None:
        """
        Create the block
        """
    def incident_row(self, incident_group: int) -> ...:
        """
        The row of the matrix for a specific incident group
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            list of doubles 
                The matrix for for the incident group 
        """
    def outgoing_column(self, outgoing_group: int) -> ...:
        """
        The column of the matrix for a specific outgoing group
        
        Parameters
        ----------
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            list of doubles 
                The matrix for for the incident group 
        """
    def p0_value(self, incident_group: int, outgoing_group: int) -> float:
        """
        The P0 matrix value for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The P0 value for the groups 
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
    def NERG(self) -> int:
        """
        The number of outgoing energy groups
        """
    @property
    def NGRP(self) -> int:
        """
        The number of incident energy groups
        """
    @property
    def block_length(self) -> int:
        """
        The length of the XSS block
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
    def number_incident_energy_groups(self) -> int:
        """
        The number of incident energy groups
        """
    @property
    def number_outgoing_energy_groups(self) -> int:
        """
        The number of outgoing energy groups
        """
    @property
    def p0_matrix(self) -> ...:
        """
        The P0 Matrix
        """
    @property
    def p0_matrix_list(self) -> ...:
        """
        The P0 matrix as a 1-D array
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class RectangularXPNData:
    """
    XPN Block for outgoing particles that are not the incident particle
    
    The RectangularXPNData class contains the XPN block for the outgoing
    particle when it is not the incident particle. 
    
    Parameters
    ----------
        matrix : array-like of int 
            the two-dimensional matrix data values 
    
    """
    def LPND(self, incident_group: int, outgoing_group: int) -> float:
        """
        The locator for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The XPN value for the groups 
        """
    def __init__(self, matrix: list[list[int]]) -> None:
        """
        Create the block
        """
    def incident_row(self, incident_group: int) -> ...:
        """
        The row of the matrix for a specific incident group
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
        
        Returns
        -------
            list of doubles 
                The matrix for for the incident group 
        """
    def locator(self, incident_group: int, outgoing_group: int) -> float:
        """
        The locator for a specific incident and outgoing group pair.
        
        Parameters
        ----------
            incident_group : int 
                 the incident group index (one-based) 
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            double 
                The XPN value for the groups 
        """
    def outgoing_column(self, outgoing_group: int) -> ...:
        """
        The column of the matrix for a specific outgoing group
        
        Parameters
        ----------
            outgoing_group : int 
                 the outgoing group index (one-based) 
        
        Returns
        -------
            list of doubles 
                The matrix for for the incident group 
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
    def NERG(self) -> int:
        """
        The number of outgoing energy groups
        """
    @property
    def NGRP(self) -> int:
        """
        The number of incident energy groups
        """
    @property
    def block_length(self) -> int:
        """
        The length of the XSS block
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
    def number_incident_energy_groups(self) -> int:
        """
        The number of incident energy groups
        """
    @property
    def number_outgoing_energy_groups(self) -> int:
        """
        The number of outgoing energy groups
        """
    @property
    def xpn_matrix(self) -> ...:
        """
        The XPN Matrix
        """
    @property
    def xpn_matrix_list(self) -> ...:
        """
        The XPN matrix as a 1-D array
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryAngularDistributionTypeBlock:
    """
    The multigroup SANG2 block with the secondary particle angular distribution types
    
    The SecondaryAngularDistributionTypeBlock class contains the secondary angular distribution 
    types. The allowed particle types are: 
    
        0  -  equi-probable cosines 
        1  -  discrete cosines 
    
    The number of secondary particle types (NSEC) is stored in NXS(8).
    
    Parameters
    ----------
        types : list of int 
            the secondary angular distribution types
    
    """
    def SANG2(self, index: int) -> int:
        """
        The angular distribution type for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The angular distribution type 
        
        Raises
        ------
            Exception 
                When the index is out of range 
        """
    def __init__(self, types: list[int]) -> None:
        """
        Create the SANG2 block
        """
    def distribution_type(self, index: int) -> int:
        """
        The angular distribution type for a secondary particle index
        
        Parameters
        ----------
            index : int 
                the index (one-based)
        
        Returns
        -------
            int 
                The angular distribution type 
        
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
    def NSEC(self) -> int:
        """
        The number of secondary particles
        """
    @property
    def SANG2s(self) -> ...:
        """
        The particle types
        """
    @property
    def distribution_types(self) -> ...:
        """
        The particle types
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
    def number_secondary_particles(self) -> int:
        """
        The number of secondary particles
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleGroupStructureBlock:
    """
    The multigroup secondary particle group structure block
    
    The SecondaryParticleGroupStructureBlock class contains 2 arrays of the same length:
      - the mean energies of each group (in MeV)
      - the widths of each group (in MeV)
    The size of each (the total number of energy groups), NERG, is LERG2(i).
    
    Parameters
    ----------
        group_means : list of floats 
            the mean energies of each group in MeV 
        group_widths : list of floats 
            the widths of each group in MeV 
    
    """
    def __init__(self, group_means: list[float], group_widths: list[float]) -> None:
        """
        Create the ERG2 block with group means and widths 
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
    def ECENT2(self) -> ...:
        """
        The mean energies of each group in MeV
        """
    @property
    def EWID2(self) -> ...:
        """
        The widths of each group MeV
        """
    @property
    def NERG(self) -> int:
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
class SecondaryParticleGroupStructureLocatorBlock:
    """
    The multigroup ERG2L block with locators for the group structure block(s)
    for the secondary particle(s)
    
    The SecondaryParticleGroupStructureLocatorBlock class contains NSEC locators, one for each
    secondary particle type given in the IPT block.
    The number of secondary particle types is stored in NXS(8).
    
    Parameters
    ----------
        locators : list of int 
            the locators for each secondary particle type
    
    """
    def ERG2(self, particle: int) -> int:
        """
        The locator for a secondary particle index 
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based)
        
        Returns
        -------
            int 
                The locator
        """
    def __init__(self, locators: list[int]) -> None:
        """
        Create the block
        """
    def locator(self, particle: int) -> int:
        """
        The locator for a secondary particle index 
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based)
        
        Returns
        -------
            int 
                The locator
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
    def NSEC(self) -> int:
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
class XPNLocatorBlock:
    """
    The multigroup XPNL block with locators for the XPN blocks 
    for the incident and secondary particles
    
    The XPNLocatorBlock class contains NSEC+1 locators, one for the incident particle
    and one for each secondary particle type given in the :class:`SecondaryParticleTypeBlock`. 
    The first locator is for the incident particle and the remaining are for the secondary 
    particles, in the same order as they are in the :class:`SecondaryParticleTypeBlock`. The 
    locators point to the XPN blocks, which contain relative locators within the PN blocks.
    
    The number of secondary particle types, NSEC, is stored in NXS(8).
    
    Parameters
    ----------
        locators : list of int 
            the locators for each XPN block
    
    """
    def LXPN(self, particle: int) -> int:
        """
        Return the locator for the XPN block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
        """
    def __init__(self, locators: list[int]) -> None:
        """
        Create the block
        """
    def is_isotropic(self, particle: int) -> bool:
        """
        Whether or not the secondary particle angular distribution is isotropic  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            bool 
                If the angular distribution is isotropic
        """
    def secondary_locator(self, particle: int) -> int:
        """
        Return the locator for the XPN block for a secondary particle index  
        
        Parameters
        ----------
            particle : int 
                the secondary particle index (one-based) in the IPT block
        
        Returns
        -------
            int 
                The locator
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
    def LXPN1(self) -> int:
        """
        The locator for the XPN block for the incident particle  
        
        Returns
        -------
            int 
                The locator
        """
    @property
    def NSEC(self) -> int:
        """
        The number of secondary particle types
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_isotropic(self) -> bool:
        """
        Whether or not the incident particle outgoing angular distribution is isotropic  
        
        Returns
        -------
            bool 
                If the angular distribution is isotropic
        """
    @property
    def incident_locator(self) -> int:
        """
        The locator for the XPN block for the incident particle  
        
        Returns
        -------
            int 
                The locator
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
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
