"""
Electron ACE blocks and components
"""
from __future__ import annotations
import typing
__all__ = ['BremsstrahlungBlock', 'ElasticAngularDistributionBlock', 'ElasticCrossSectionBlock', 'ElectronShellBlock', 'ElectronSubshellBlock', 'EnergyDistributionBlock', 'ExcitationBlock', 'PrincipalCrossSectionBlock', 'SubshellTransitionData', 'SubshellTransitionDataBlock', 'TabulatedAngularDistribution', 'TabulatedEnergyDistribution']
class BremsstrahlungBlock:
    """
    The electron BREML block with the average electron energy after Bremsstrahlung
    
    This block is part of the eprdata formats.
    
    The BremsstrahlungBlock class contains 2 arrays of the same length:
      - the energy points
      - the average energy remaining after Bremsstrahlung
    
    The size NBL of each (the total number of energy points) is stored in NXS(12).
    """
    def __init__(self, energies: list[float], remaining: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self         the block
            energies     the energy values
            remaining    the average energy remaining after Bremsstrahlung
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
    def NBL(self) -> int:
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
        The energy values
        """
    @property
    def energy_after_bremsstrahlung(self) -> ...:
        """
        The average energy remaining after Bremsstrahlung
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
class ElasticAngularDistributionBlock:
    """
    The electron ELASI and ELAS block with the large angle elastic scattering
    angular distribution data
    
    The ElasticAngularDistributionBlock class contains a list of electron energies
    for which angular distribution data is given.
    """
    def LLOC(self, index: int) -> int:
        """
        Return the relative distribution locator for an energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, distributions: list[TabulatedAngularDistribution]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the angular distribution data
        """
    def distribution(self, index: int) -> TabulatedAngularDistribution:
        """
        Return the angular distribution for an energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an energy index
        
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
    def NA(self) -> int:
        """
        The number of available energies
        """
    @property
    def distributions(self) -> list[TabulatedAngularDistribution]:
        """
        The angular distribution data
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
        The number of available energies
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ElasticCrossSectionBlock:
    """
    The electron SELAS block with the additional electron elastic cross section data
    
    This block is part of the eprdata14 format.
    
    The ElasticCrossSectionBlock class contains 2 arrays of the same length:
      - the transport elastic scattering cross section
      - the total elastic scattering cross section
    
    The size NE of each (the total number of electron energy points) is stored in
    NXS(8).
    """
    def __init__(self, transport: list[float], total: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self         the block
            transport    the transport elastic cross section values
            total        the total elastic cross section values
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
    def NE(self) -> int:
        """
        The number of energy points
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
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def total(self) -> ...:
        """
        The total elastic cross section values
        """
    @property
    def transport(self) -> ...:
        """
        The transport elastic cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ElectronShellBlock:
    """
    The electron LNEPS, LBEPS and LPIPS block with the electron shell data
    
    The ElectronShellBlock class contains 3 arrays of the same length:
      - the number of electrons for each shell
      - the binding energy for each shell
      - the interaction probability for each shell
    The size of each (the total number of electron shells) is stored in NXS(5).
    """
    def __init__(self, electrons: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            electrons        the number of electrons for each shell
            energies         the binding energy for each shell
            probabilities    the interaction probability for each shell
        """
    def binding_energy(self, index: int) -> float:
        """
        The binding energy for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def interaction_probability(self, index: int) -> float:
        """
        The interaction probability for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def number_electrons_per_shell(self, index: int) -> int:
        """
        The number of electrons on a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
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
    def LBEPS(self) -> ...:
        """
        The binding energies for each shell
        """
    @property
    def LNEPS(self) -> ...:
        """
        The number of electrons for each shell
        """
    @property
    def LPIPS(self) -> ...:
        """
        The interaction probability for each shell
        """
    @property
    def NSH(self) -> int:
        """
        The number of electron shells
        """
    @property
    def binding_energies(self) -> ...:
        """
        The binding energies for each shell
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def interaction_probabilities(self) -> ...:
        """
        The interaction probability for each shell
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
    def number_electron_shells(self) -> int:
        """
        The number of electron shells
        """
    @property
    def number_electrons(self) -> ...:
        """
        The number of electrons for each shell
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ElectronSubshellBlock:
    """
    The electron SUBSH block with the electron subshell data
    
    This block is part of the eprdata formats.
    
    The ElectronSubshellBlock class contains 5 arrays of the same length:
      - the ENDF designator of each subshell
      - the electron population for each subshell
      - the binding energy for each subshell
      - the vacancy cumulative probability for each subshell
      - the number of possible transitions to fill a vacancy for each subshell
    The size of each (the total number of electron shells) is stored in NXS(7).
    """
    def __init__(self, designators: list[int], electrons: list[float], energies: list[float], probabilities: list[float], transitions: list[int]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            designators      the ENDF designator of each subshell
            electrons        the electron population for each subshell
            energies         the vacancy cumulative probability for each subshell
            probabilities    the number of possible transitions to fill a vacancy
                             for each subshell
        """
    def binding_energy(self, index: int) -> float:
        """
        The binding energy for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def designator(self, index: int) -> int:
        """
        The ENDF designator for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def population(self, index: int) -> float:
        """
        The electron population for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def transitions(self, index: int) -> int:
        """
        The number of transitions to fill a vacancy for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
        """
    def vacancy_probability(self, index: int) -> float:
        """
        The vacancy probability for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
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
    def BE(self) -> ...:
        """
        The binding energies for each subshell
        """
    @property
    def CV(self) -> ...:
        """
        The vacancy probabilities for each subshell
        """
    @property
    def EP(self) -> ...:
        """
        The electron population for each subshell
        """
    @property
    def ID(self) -> ...:
        """
        The number of electron shells
        """
    @property
    def NSSH(self) -> int:
        """
        The number of electron subshells
        """
    @property
    def NT(self) -> ...:
        """
        The number of transitions to fill a vacancy for each subshell
        """
    @property
    def binding_energies(self) -> ...:
        """
        The binding energies for each subshell
        """
    @property
    def designators(self) -> ...:
        """
        The number of electron shells
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
    def number_electron_subshells(self) -> int:
        """
        The number of electron subshells
        """
    @property
    def number_transitions(self) -> ...:
        """
        The number of transitions to fill a vacancy for each subshell
        """
    @property
    def populations(self) -> ...:
        """
        The electron population for each subshell
        """
    @property
    def vacancy_probabilities(self) -> ...:
        """
        The vacancy probabilities for each subshell
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EnergyDistributionBlock:
    """
    The energy distribution block for photons from Bremsstrahlung or knock-on
    electrons for a specific subshell
    
    The EnergyDistributionBlock class contains a list of electron energies
    for which energy distribution data is given (for either photons in the
    BREMI/BREME block or electrons in the EION blocks).
    """
    def LLOC(self, index: int) -> int:
        """
        Return the relative distribution locator for an energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, distributions: list[TabulatedEnergyDistribution]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the energy distribution data
        """
    def distribution(self, index: int) -> TabulatedEnergyDistribution:
        """
        Return the angular distribution for an energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an energy index
        
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
    def NB(self) -> int:
        """
        The number of available energies
        """
    @property
    def distributions(self) -> list[TabulatedEnergyDistribution]:
        """
        The angular distribution data
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
        The number of available energies
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ExcitationBlock:
    """
    The electron EXCIT block with the electron excitation energy loss data
    
    This block is part of the eprdata formats.
    
    The ExcitationBlock class contains 2 arrays of the same length:
      - the energy points
      - the average excitation energy loss values
    
    The size NXL of each (the total number of excitation energy points) is
    stored in NXS(9).
    """
    def __init__(self, energies: list[float], loss: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energies    the energy values
            loss        the average excitation energy loss values
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
    def NXL(self) -> int:
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
        The energy values
        """
    @property
    def excitation_energy_loss(self) -> ...:
        """
        The average excitation energy loss values
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
class PrincipalCrossSectionBlock:
    """
    The electron ESZE block with the electron cross section data
    
    This block is part of the eprdata formats.
    
    The PrincipalCrossSectionBlock class contains 5 + NSSH arrays of the same length:
      - the energy points
      - the total cross section (sum of the following three arrays)
      - the large angle elastic scattering cross section
      - the Bremsstrahlung cross section
      - the excitation cross section
      - the total electroionisation cross section (sum of the following NSSH arrays)
      - the electroionisation cross section for each subshell (NSSH arrays)
    
    The size NE of each (the total number of electron energy points) is stored in
    NXS(8). The number of subshells NSSH is stored in NXS(7).
    """
    def __init__(self, energies: list[float], elastic: list[float], bremsstrahlung: list[float], excitation: list[float], electroionisation: list[list[float]]) -> None:
        """
        Initialise the block
        
        Arguments:
            self                 the block
            energies             the energy values
            elastic              the elastic cross section values
            bremsstrahlung       the Bremsstrahlung cross section values
            excitation           the excitation cross section values
            electroionisation    the electroionisation cross section values
        """
    def electroionisation(self, index: int) -> ...:
        """
        The electroionisation cross section values for a specific shell
        
        Arguments:
            self     the block
            index    the electron shell index (one-based)
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
    def NE(self) -> int:
        """
        The number of energy points
        """
    @property
    def NSSH(self) -> int:
        """
        The number of electron subshells
        """
    @property
    def bremsstrahlung(self) -> ...:
        """
        The Bremsstrahlung cross section values
        """
    @property
    def elastic(self) -> ...:
        """
        The large angle elastic cross section values
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
    def excitation(self) -> ...:
        """
        The excitation cross section values
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
    def number_electron_subshells(self) -> int:
        """
        The number of electron subshells
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
    def total_electroionisation(self) -> ...:
        """
        The total electroionisation cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SubshellTransitionData:
    """
    The electron transition data for a given subshell
    
    This block is part of the eprdata formats.
    
    The SubshellTransitionData class contains the transition data to fill vacancies
    in the given subshell. Each transition has the following information associated to it:
      - the primary subshell designator (the designator of the subshell from
        where the electron is "moving" from)
      - the secondary subshell designator (the designator of the subshell from
        which the emitted electron is ejected or 0 for a radiative transition
        that only emits a photon)
      - the energy of the emitted photon or electron
      - the cumulative probability of the transition
    
    The size NT of each (the total number of transitions) is stored in the SUBSH
    block. This data block may be empty (NT = 0).
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise an empty block
        """
    @typing.overload
    def __init__(self, primary: list[int], secondary: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            primary          the primary subshell designators
            secondary        the secondary subshell designators
            energies         the energy values of the secondary photon or electron
            probabilities    the cumulative probabilities of the transitions
        """
    def energy(self, index: int) -> float:
        """
        The energy of the secondary photon or electron for a given transition
        
        Arguments:
            self     the block
            index    the transition index (one-based)
        """
    def is_radiative_transition(self, index: int) -> bool:
        """
        Return whether or not the transition is a radiative transitions
        
        Arguments:
            self     the block
            index    the transition index (one-based)
        """
    def primary_designator(self, index: int) -> int:
        """
        The primary designator for a given transition
        
        Arguments:
            self     the block
            index    the transition index (one-based)
        """
    def probability(self, index: int) -> float:
        """
        The cumulative probability for a given transition
        
        Arguments:
            self     the block
            index    the transition index (one-based)
        """
    def secondary_designator(self, index: int) -> int:
        """
        The secondary designator for a given transition
        
        Arguments:
            self     the block
            index    the transition index (one-based)
        """
    def transition(self, arg0: int) -> ...:
        """
        The transition data for a given transition
        
        Arguments:
            self     the block
            index    the transition index (one-based)
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
    def NT(self) -> int:
        """
        The number of transitions
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
    def number_transitions(self) -> int:
        """
        The number of transitions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SubshellTransitionDataBlock:
    """
    The electron RELO and XPROB block with the transition data
    
    The SubshellTransitionDataBlock class contains the transition data for each
    subshell (the number of subshells NSSH is stored in NXS(7)).
    """
    def LTRAN(self, index: int) -> int:
        """
        Return the relative transition data locator for a subshell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, transitions: list[SubshellTransitionData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self           the block
            transitions    the transition data
        """
    def transition_data(self, index: int) -> SubshellTransitionData:
        """
        Return the transition data for a subshell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def transition_data_locator(self, index: int) -> int:
        """
        Return the relative transition data locator for a subshell index
        
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
    def NSSH(self) -> int:
        """
        The number of electron subshells
        """
    @property
    def data(self) -> list[SubshellTransitionData]:
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
    def number_electron_subshells(self) -> int:
        """
        The number of electron subshells
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedAngularDistribution:
    """
    Tabulated electron angular distribution data for a single incident energy
    
    The TabulatedAngularDistribution class contains the cumulative density function
    (CDF) as a function of cosine for the given incident energy. It is used in
    the ELAS block.
    """
    def __init__(self, energy: float, cosines: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            energy          the associated incident energy value
            cosines         the cosine values
            cdf             the cdf values
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
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy(self) -> float:
        """
        The associated incident energy value
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
    def number_cosines(self) -> int:
        """
        The number of cosine values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedEnergyDistribution:
    """
    Tabulated photon energy distribution from Bremsstrahlung for a single incident energy
    
    The TabulatedEnergyDistribution class contains the cumulative density function
    (CDF) as a function of photon energy for the given incident energy. It is used
    in the BREME block.
    """
    def __init__(self, energy: float, outgoing: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energy      the associated incident energy value
            outgoing    the outgoing energy values
            cdf         the cdf values
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
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy(self) -> float:
        """
        The associated incident energy value
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
    def number_outgoing_energies(self) -> int:
        """
        The number of outgoing energy values
        """
    @property
    def outgoing_energies(self) -> ...:
        """
        The cosine values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
