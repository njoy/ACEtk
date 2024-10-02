"""
Photoatomic ACE blocks and components
"""
from __future__ import annotations
import typing
__all__ = ['CoherentFormFactorBlock', 'ComptonProfile', 'ComptonProfileBlock', 'FluorescenceDataBlock', 'HeatingNumbersBlock', 'IncoherentScatteringFunctionBlock', 'PhotoelectricCrossSectionBlock', 'PrincipalCrossSectionBlock']
class CoherentFormFactorBlock:
    """
    The photoatomic JCOH block with the coherent form factors
    
    The CoherentFormFactorBlock class contains coherent form factors that are
    used to modify the differential Thomson cross sectiontabulated on a fixed
    grid of the recoil electron momentum transfer (in inverse angstroms).
    """
    @typing.overload
    def __init__(self, integrated: list[float], factors: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self          the block
            integrated    the integrated form factor values
            factors       the form factor values
        """
    @typing.overload
    def __init__(self, momentum: list[float], integrated: list[float], factors: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self          the block
            momentum      the momentum values
            integrated    the integrated form factor values
            factors       the form factor values
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
    def NM(self) -> int:
        """
        The number of values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def form_factors(self) -> ...:
        """
        The form factor values
        """
    @property
    def integrated_form_factors(self) -> ...:
        """
        The integrated form factor values
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def momentum(self) -> ...:
        """
        The electron recoil momentum values
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ComptonProfile:
    """
    Tabulated Compton profile data for a given electron shell
    
    The ComptonProfile class contains the probability density function (PDF) and
    cumulative density function (CDF) as a function of momentum. It is used in
    the LSWD block.
    """
    def __init__(self, interpolation: int, momentum: list[float], pdf: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            interpolation   the interpolation type
            momentum        the cosine values (N values)
            pdf             the pdf values (N values)
            cdf             the cdf values (N values)
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
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def momentum(self) -> ...:
        """
        The momentum values
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ComptonProfileBlock:
    """
    The photoatomic LSWD and SWD block with the compton profile data
    
    The ComptonProfileBlock class contains NXS(5) sets of compton profiles, one
    for each electron shell.
    """
    def LSWD(self, index: int) -> int:
        """
        Return the relative compton profile locator for an electron shell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, profiles: list[ComptonProfile]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            profiles    the compton profile data
        """
    def compton_profile(self, index: int) -> ComptonProfile:
        """
        Return the compton profile for an electron shell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def compton_profile_locator(self, index: int) -> int:
        """
        Return the relative compton profile locator for an electron shell index
        
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
    def NSH(self) -> int:
        """
        The number of electron shells
        """
    @property
    def data(self) -> list[ComptonProfile]:
        """
        The compton profiles
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
    def number_electron_shells(self) -> int:
        """
        The number of electron shells
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FluorescenceDataBlock:
    """
    The photoatomic JFLO block with the fluorescence data
    
    The FluorescenceDataBlock class contains 4 arrays of the same length:
      - the fluoresence edge energies
      - the relative ejection probabilities
      - the yields
      - the fluorescent energies
    The size of each (the total number of fluorescence edges) is stored in NXS(4).
    """
    def __init__(self, edges: list[float], probabilities: list[float], yields: list[float], energies: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            edges            the edge energies
            probabilities    the ejection probabilities
            yields           the yields
            energies         the fluorescent energies
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
    def E(self) -> ...:
        """
        The fluoresence edge energies
        """
    @property
    def F(self) -> ...:
        """
        The fluorescent energies
        """
    @property
    def NFLO(self) -> int:
        """
        The number of fluoresence edges
        """
    @property
    def PHI(self) -> ...:
        """
        The relative ejection probabilities
        """
    @property
    def Y(self) -> ...:
        """
        The yields
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def fluorescence_edge_energies(self) -> ...:
        """
        The fluoresence edge energies
        """
    @property
    def fluorescent_energies(self) -> ...:
        """
        The fluorescent energies
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
    def number_fluorescence_edges(self) -> int:
        """
        The number of electron shells
        """
    @property
    def relative_ejection_probabilities(self) -> ...:
        """
        The relative ejection probabilities
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
    @property
    def yields(self) -> ...:
        """
        The yields
        """
class HeatingNumbersBlock:
    """
    The photoatomic LHNM block with the heating numbers
    
    The HeatingNumbersBlock class contains the heating numbers. The size of the
    array is stored in NXS(3) and the corresponding energy points can be found
    in the ESZG block.
    """
    def __init__(self, heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self       the block
            heating    the heating numbers
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
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def heating(self) -> ...:
        """
        The heating number
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
class IncoherentScatteringFunctionBlock:
    """
    The photoatomic JINC block with the incoherent scattering function
    
    The IncoherentScatteringFunctionBlock class contains one of the following
    representations of the scattering function:
      - 21 scattering function values using a fixed momentum grid (mcplib version)
      - tabulated momentum and scattering function values (eprdata version)
    
    The interface abstracts away the distinction between the two representations.
    
    The recoil electron momentum transfer values are given in inverse angstroms.
    """
    @typing.overload
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the block using the mcplib representation
        
        Arguments:
            self       the block
            values     the incoherent scattering function values (21 in total)
        """
    @typing.overload
    def __init__(self, momentum: list[float], values: list[float]) -> None:
        """
        Initialise the block using the eprdata representation
        
        Arguments:
            self        the block
            momentum    the momentum values    values      the incoherent scattering function values
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
    def NM(self) -> int:
        """
        The number of values
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
    def momentum(self) -> ...:
        """
        The electron recoil momentum values
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def values(self) -> ...:
        """
        The incoherent scattering function values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PhotoelectricCrossSectionBlock:
    """
    The photoatomic SPHEL block with the photoelectric cross section for each subshell
    
    This block is part of the eprdata formats.
    
    The PhotoelectricCrossSectionBlock class contains NSSH arrays of the same
    length, each one being the photoelectric cross section of a subshell.
    
    The size of each (the total number of energy points NES) is stored in NXS(3).
    """
    def __init__(self, photoelectric: list[list[float]]) -> None:
        """
        Initialise the block
        
        Arguments:
            self              the block
            photoelectric    the photoelectric cross section values for each shell
        """
    def photoelectric(self, index: int) -> ...:
        """
        The photoelectric cross section values for a specific shell
        
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
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def NSSH(self) -> int:
        """
        The number of electron subshells
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
    The photoatomic ESZG block with the principal cross sections
    
    The PrincipalCrossSectionBlock class contains 5 arrays of the same length
    (all values are stored as the natural logarithm):
      - the energy points
      - the incoherent cross section
      - the coherent cross section
      - the photoelectric cross section
      - the pair production cross section
    
    The size of each (the total number of energy points) is stored in NXS(3).
    """
    def __init__(self, energies: list[float], incoherent: list[float], coherent: list[float], photoelectric: list[float], pairproduction: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self              the block
            energies          the energy values
            incoherent        the incoherent cross section values
            coherent          the coherent cross section values
            photoelectric     the photoelectric cross section values
            pairproduction    the pair production cross section values
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
    def coherent(self) -> ...:
        """
        The coherent cross section values
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
    def incoherent(self) -> ...:
        """
        The incoherent cross section values
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
    def pairproduction(self) -> ...:
        """
        The pair production cross section values
        """
    @property
    def photoelectric(self) -> ...:
        """
        The photoelectric cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
