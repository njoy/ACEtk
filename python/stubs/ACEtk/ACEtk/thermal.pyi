"""
Thermal scattering ACE blocks and components
"""
from __future__ import annotations
import typing
__all__ = ['CrossSectionBlock', 'DiscreteCosines', 'DiscreteCosinesWithProbability', 'ElasticAngularDistributionBlock', 'InelasticAngularDistributionBlock']
class CrossSectionBlock:
    """
    The thermal scattering cross section block
    """
    def __init__(self, energies: list[float], xs: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energies    the inelastic energies
            xs          the inelastic cross section values
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
        The number of energies
        """
    @property
    def cross_sections(self) -> ...:
        """
        The inelastic cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The inelastic energies
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
    def number_incident_energies(self) -> int:
        """
        The number of energies
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DiscreteCosines:
    """
    Discrete cosines for a single outgoing energy value used in thermal scattering secondary particle distributions
    
    The DiscreteCosines class contains an outgoing energy value and the
    associated discrete cosine values. It is used in the ITXE block (for
    inelastic thermal scattering data) when IFENG = 0 or 1.
    """
    def __init__(self, energy: float, cosines: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energy      the outgoing energy value
            cosines     the cosine values
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
    def NC(self) -> int:
        """
        The number of discrete cosines
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
        The outgoing energy value
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
    def number_discrete_cosines(self) -> int:
        """
        The number of discrete cosines
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DiscreteCosinesWithProbability:
    """
    Discrete cosines for a single outgoing energy value used in thermal scattering secondary particle distributions
    
    The DiscreteCosinesWithProbability class contains an outgoing energy value,
    the corresponding pdf and cdf value and the associated discrete cosine values.
    It is used in the ITXE block (for inelastic thermal scattering data) when
    IFENG = 2. This is the current standard ACE format used in inelastic thermal
    scattering.
    """
    def __init__(self, energy: float, pdf: float, cdf: float, cosines: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self       the block
            energy     the outgoing energy value
            pdf        the pdf value
            cdf        the cdf value
            cosines    the cosine values
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
    def NC(self) -> int:
        """
        The number of discrete cosines
        """
    @property
    def cdf(self) -> float:
        """
        The cdf value
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
        The outgoing energy value
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
    def number_discrete_cosines(self) -> int:
        """
        The number of discrete cosines
        """
    @property
    def pdf(self) -> float:
        """
        The pdf  value
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ElasticAngularDistributionBlock:
    """
    The angular distribution block for inelastic thermal scattering
    
    The ElasticAngularDistributionBlock class contains the equiprobable set or
    a skewed distribution of discrete cosines, or a tabulated probability distribution.
    """
    def __init__(self, cosines: list[list[float]]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            cosines     the discrete cosine values for each incident energy
        """
    def cosines(self, index: int) -> ...:
        """
        The cosine values for an incident energy index
        
        When the index is out of range an std::out_of_range exception is thrown
        (debug mode only).
        
        index    the incident energy index (one-based)
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
    def NC(self) -> int:
        """
        The number of equiprobable discrete cosine values for each incident and outgoing energy pair
        """
    @property
    def NCL(self) -> int:
        """
        The elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def elastic_dimensioning_parameter(self) -> int:
        """
        The elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
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
    def number_discrete_cosines(self) -> int:
        """
        The number of equiprobable discrete cosine values for each incident and outgoing energy pair
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class InelasticAngularDistributionBlock:
    """
    The angular distribution block for inelastic thermal scattering
    
    The InelasticAngularDistributionBlock class contains the equiprobable set
    or a skewed distribution of discrete cosines, or a tabulated probability
    distribution.
    """
    def NIEB(self, index: int) -> int:
        """
        The number of secondary energies for an incident energy index
        
        When the index is out of range an std::out_of_range exception is thrown
        (debug mode only).
        
        index    the incident energy index (one-based)
        """
    @typing.overload
    def __init__(self, cosines: list[list[DiscreteCosines]], skewed: bool, locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            cosines     the discrete cosine data for each incident and outgoing energy value
            skewed      flag to indicate whether or not the distribution is skewed or equiprobable
            locb        the starting xss index for the ITXE block (default = 1)
        """
    @typing.overload
    def __init__(self, cosines: list[list[DiscreteCosinesWithProbability]], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            cosines     the discrete cosine data for each incident and outgoing energy value
            locb        the starting xss index for the ITXE block (default = 1)
        """
    def discrete_cosine_data(self, incident: int, outgoing: int) -> DiscreteCosines | DiscreteCosinesWithProbability:
        """
        The discrete cosine data for an incident and outgoing energy index
        
        When the index is out of range an std::out_of_range exception is thrown
        (debug mode only).
        
        incident    the incident energy index (one-based)
        outgoing    the outgoing energy index (one-based)
        """
    def number_outgoing_energies(self, index: int) -> int:
        """
        The number of secondary energies for an incident energy index
        
        When the index is out of range an std::out_of_range exception is thrown
        (debug mode only).
        
        index    the incident energy index (one-based)
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
    def IFENG(self) -> int:
        """
        The secondary energy mode
        """
    @property
    def NC(self) -> int:
        """
        The number of equiprobable discrete cosine values for each incident and outgoing energy pair
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def NIL(self) -> int:
        """
        The inelastic dimensioning parameter
        
        For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
        for IFENG = 2 this will be equal to NC + 1
        """
    @property
    def data(self) -> list[list[DiscreteCosines | DiscreteCosinesWithProbability]]:
        """
        The angular distribution data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def inelastic_dimensioning_parameter(self) -> int:
        """
        The inelastic dimensioning parameter
        
        For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
        for IFENG = 2 this will be equal to NC + 1
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
    def number_discrete_cosines(self) -> int:
        """
        The number of equiprobable discrete cosine values for each incident and outgoing energy pair
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def secondary_energy_mode(self) -> int:
        """
        The number of discrete cosines
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
